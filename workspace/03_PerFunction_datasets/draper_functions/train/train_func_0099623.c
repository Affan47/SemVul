histogram_print_matlab(histogram* h, FILE* fid) {
	int i;
	fprintf(fid, "[ ");
	for (i=0; i<h->Nbins; i++)
		fprintf(fid, "%s%i", (i ? ", " : ""), h->hist[i]);
	fprintf(fid, "]");
}
