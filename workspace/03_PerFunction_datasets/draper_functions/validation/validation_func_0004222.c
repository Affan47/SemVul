esa_print_gsa(t_GSA *GSA, size_t size){

	#if BWT
		printf("i\t|text, suff \t(lcp) \t(bwt)\n");
	#else
		printf("i\t|text, suff \t(lcp)\n");
	#endif

	size_t i = 0;
	for(; i < size; i++){
		#if BWT
			printf("%zu\t|%u, %u \t(%u) \t(%d)\n", i, GSA[i].text, GSA[i].suff, GSA[i].lcp, GSA[i].bwt);
		#else
			printf("%zu\t|%u, %u \t(%u) \n", i, GSA[i].text, GSA[i].suff, GSA[i].lcp);
		#endif
	}

return 0;
}
