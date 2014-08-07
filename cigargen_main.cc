//============================================================================
// Name        : cigargen.cpp
// Author      : Ivan Sovic
// Version     :
// Copyright   : Copyright Ivan Sovic, 2014. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "cigargen.h"

using namespace std;

int main() {
  std::string reference = "ACTGCTGCCTGCAAAAAAAAAAA";
  std::string query = "AGTGTGCCCT";

  std::string cigar;
  std::string alignment = "";
  int32_t alignment_length = GenerateCigar((char *) query.c_str(), query.size(), (char *) reference.c_str(), reference.size(), &cigar, &alignment);

  printf ("Reference sequence:\t%s\n", reference.c_str());
  printf ("Query sequence:\t\t%s\n", query.c_str());
  printf ("Returned CIGAR: %s\n", cigar.c_str());
  printf ("Alignment: %s\n", alignment.c_str());
  printf ("Alignment length: %d\n", alignment_length);

	return 0;
}
