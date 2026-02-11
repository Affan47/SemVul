find_inverse(int_suff* SA, int_suff **ISA, int_suff n){

	(*ISA) = (int_suff*) malloc(n * sizeof(int_suff));

	int_suff i;
	for(i = 0; i < n; i++)
		((*ISA)[SA[i]]) = i;


}
