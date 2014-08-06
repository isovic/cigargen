/*
 * cigargen.h
 *
 *  Created on: Aug 6, 2014
 *      Author: ivan
 */

#ifndef CIGARGEN_H_
#define CIGARGEN_H_

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Convert aligned sequences to corresponding Compact Idiosyncratic Gapped Alignment Report (CIGAR) format strings (this full name of the accronym was found on http://www.mathworks.com/help/bioinfo/ref/align2cigar.html).
int GenerateCigar(char *query, uint32_t query_length, char *reference, uint32_t reference_length, std::string *ret_cigar);
void Verbose(FILE *fp, char *query, uint32_t query_length, char *reference, uint32_t reference_length, std::string ret_cigar, std::vector<std::vector<int32_t> > &dp_matrix, std::vector<std::vector<uint8_t> > &dp_traceback);

#endif /* CIGARGEN_H_ */
