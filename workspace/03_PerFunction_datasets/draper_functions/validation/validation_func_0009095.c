zIsGenomicOnly(zStrIdx state) {
	return (zIsIntron(state) ||
	        strcmp(zStrIdx2Char(state), "RGenomic1") == 0 ||
	        strcmp(zStrIdx2Char(state), "RGenomic2") == 0 ||
	        strcmp(zStrIdx2Char(state), "Genomic")   == 0 );
}
