Simple dynamic programming implementation of sequence alignment for generating CIGAR strings.
For alignment, Needleman-Wunsch is used.
The general assumption is that the query and the reference are supposed to start on the beginning (i.e. after obtaining the starting position of the query on the reference, reference is trimmed to that local region, where its index 0 is query's starting position).

