UnionBlock(b_type B1, b_type B2)

{
	long	j;
	if(B1->N != B2->N) {
		fprintf(stderr,"N1=%ld, N2=%ld\n",B1->N,B2->N);
		blockerror("N1!=N2 for Union operation");
	}
	if(B1->list != NULL) update_list_block(B1);
	if(B2->list != NULL) update_list_block(B2);
	for(j=0;j<B1->nint;j++)
		B1->i[j] = B1->i[j] | B2->i[j];
	return B1;
}
