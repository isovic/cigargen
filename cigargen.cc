/*
 * cigargen.cc
 *
 *  Created on: Aug 6, 2014
 *      Author: ivan
 */

#include "cigargen.h"

#define MATCH      5
#define MISMATCH  -2
#define INSERTION -6
#define DELETION  -6

inline char TypeToSymbol(uint8_t type) {
  if (type == 0)
    return 'M';
  else if (type == 1)
    return 'X';
  else if (type == 2)
    return 'I';
  else if (type == 3)
    return 'D';

  return 'X';
}

int GenerateCigar(char *query, uint32_t query_length, char *reference, uint32_t reference_length, std::string *ret_cigar) {
  if (query == NULL || reference == NULL || query_length == 0 || reference_length == 0)
    return 1;

  std::vector<std::vector<int32_t> > dp_matrix((query_length + 1), std::vector<int32_t>((reference_length + 1), 0));
  std::vector<std::vector<uint8_t> > dp_traceback((query_length + 1), std::vector<uint8_t>((reference_length + 1), 0));
  int32_t up=0, left=0, diagonal=0;

  for (uint32_t i=0; i<=query_length; i++)
    dp_matrix[i][0] = i * INSERTION;
  for (uint32_t i=0; i<=reference_length; i++)
    dp_matrix[0][i] = i * DELETION;

  for (uint32_t i=1; i<=query_length; i++) {
    for (uint32_t j=1; j<=reference_length; j++) {
      up = dp_matrix[i-1][j] + INSERTION;
      left = dp_matrix[i][j-1] + DELETION;
      diagonal = dp_matrix[i-1][j-1] + ((query[i-1] == reference[j-1])?MATCH:MISMATCH);

      dp_matrix[i][j] = diagonal;
      dp_traceback[i][j] = ((query[i-1] == reference[j-1])?0:1);
      if (up > dp_matrix[i][j]) {
        dp_matrix[i][j] = up;
        dp_traceback[i][j] = 2;
      }
      if (left > dp_matrix[i][j]) {
        dp_matrix[i][j] = left;
        dp_traceback[i][j] = 3;
      }
    }
  }

  int32_t max_score_index=0, current_traceback_row=query_length, current_traceback_column=0;
  for (uint32_t i=0; i<=reference_length; i++) {
    if (dp_matrix[query_length][i] > dp_matrix[query_length][max_score_index])
      max_score_index = i;
  }
  current_traceback_column = max_score_index;

//  std::string long_cigar = "";
  std::stringstream cigar_stream;
  std::string cigar = "";

  uint32_t iterations=0, last_type=0, num_same_types=0;
  while (current_traceback_column > 0 && current_traceback_row > 0) {
    if (iterations == 0) {
      last_type = dp_traceback[current_traceback_row][current_traceback_column];
      num_same_types = 1;
    }
    else {
      if (dp_traceback[current_traceback_row][current_traceback_column] == last_type) {
        num_same_types += 1;
      }
      else {
        cigar_stream << TypeToSymbol(last_type) << num_same_types;
        last_type = dp_traceback[current_traceback_row][current_traceback_column];
        num_same_types = 1;
      }
    }

    if (dp_traceback[current_traceback_row][current_traceback_column] == 0) {
//      long_cigar = std::string("M") + long_cigar;
      current_traceback_row -= 1;
      current_traceback_column -= 1;
    }
    else if (dp_traceback[current_traceback_row][current_traceback_column] == 1) {
//      long_cigar = std::string("X") + long_cigar;
      current_traceback_row -= 1;
      current_traceback_column -= 1;
    }
    else if (dp_traceback[current_traceback_row][current_traceback_column] == 2) {
//      long_cigar = std::string("I") + long_cigar;
      current_traceback_row -= 1;
    }
    else if (dp_traceback[current_traceback_row][current_traceback_column] == 3) {
//      long_cigar = std::string("D") + long_cigar;
      current_traceback_column -= 1;
    }

    iterations += 1;
  }

  cigar_stream << TypeToSymbol(last_type) << num_same_types;
  cigar = cigar_stream.str();
  std::reverse(cigar.begin(), cigar.end());

  if (ret_cigar != NULL)
    *ret_cigar = cigar;

  return 0;
}

void Verbose(FILE *fp, char *query, uint32_t query_length, char *reference, uint32_t reference_length, std::string ret_cigar, std::vector<std::vector<int32_t> > &dp_matrix, std::vector<std::vector<uint8_t> > &dp_traceback) {
  fprintf (fp, "%3c", ' ');
  for (uint32_t i=0; i<=reference_length; i++) {
    if (i > 0)
      fprintf (fp, "%3c", reference[i-1]);
    else
      fprintf (fp, "%3c", '-');
  }
  fprintf (fp, "\n");

  for (uint32_t i=0; i<=query_length; i++) {
    if (i > 0)
      fprintf (fp, "%3c", query[i-1]);
    else
      fprintf (fp, "%3c", '-');

    for (uint32_t j=0; j<=reference_length; j++) {
      fprintf (fp, "%3d", dp_matrix[i][j]);
    }
    fprintf (fp, "\n");
  }

  fprintf (fp, "\n");
  fprintf (fp, "Traceback:\n");

  fprintf (fp, "%3c", ' ');
  for (uint32_t i=0; i<=reference_length; i++) {
    if (i > 0)
      fprintf (fp, "%3c", reference[i-1]);
    else
      fprintf (fp, "%3c", '-');
  }
  fprintf (fp, "\n");

  for (uint32_t i=0; i<=query_length; i++) {
    if (i > 0)
      fprintf (fp, "%3c", query[i-1]);
    else
      fprintf (fp, "%3c", '-');

    for (uint32_t j=0; j<=reference_length; j++) {
      fprintf (fp, "%3d", dp_traceback[i][j]);
    }
    fprintf (fp, "\n");
  }

  fprintf (fp, "\n");

  fprintf (fp, "CIGAR: %s\n", ret_cigar.c_str());
  fprintf (fp, "\n");
}
