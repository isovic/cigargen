Simple dynamic programming implementation of sequence alignment for generating CIGAR strings.

Generates "Compact Idiosyncratic Gapped Alignment Report" (CIGAR) format strings. Implemented using Needleman-Wunsch dynamic programming algorithm. Because of this, query and reference are supposed to be aligned to the left of both sequences, i.e. a result of sequence alignment which can be found in SAM files reports the starting position of an alignment. This location on the reference needs to be used as the beginning of the reference which is passed to GenerateCigar function.

This function is a basic implementation, which is quadratic in both time and memory.

Example usage is given in the `cigargen_main.cc` file:
```
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
```
Output of the above code snippet should be:
```
  Reference sequence:	ACTGCTGCCTGCAAAAAAAAAAA
  Query sequence:		AGTGTGCCCT
  Returned CIGAR: 1M1X2M1D2M1I3M
  Alignment: AxTG-TG+CCT
  Alignment length: 10
```

Detailed description of parameters can be found in the `cigargen.h` file.

Copyright Ivan Sovic, 2014.
Licence type: MIT.


