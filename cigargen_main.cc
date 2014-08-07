//============================================================================
// Name        : cigargen.cpp
// Author      : Ivan Sovic
// Version     :
// Copyright   : Copyright Ivan Sovic, 2014. All rights reserved.
// Description : CIGAR string generator example.
//============================================================================

#include <string>
#include "cigargen.h"

//  The MIT License (MIT)
//
//  Copyright (c) 2014 Ivan Sovic
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.



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
