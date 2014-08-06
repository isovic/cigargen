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
  std::string query = "AGTGTG";

  reference = "ACGTATGC";
  query = "ACGATGC";
  query = "ACGTTGC";
  query = "GTATC";

  std::string cigar;
  GenerateCigar((char *) query.c_str(), query.size(), (char *) reference.c_str(), reference.size(), &cigar);

  printf ("Returned CIGAR: %s\n", cigar.c_str());

	return 0;
}
