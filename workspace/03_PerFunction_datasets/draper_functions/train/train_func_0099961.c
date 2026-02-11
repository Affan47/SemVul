atoi2(const char *n) {
	uint32_t retval=0;
	int i,m;
	if (n==NULL) return(0);
	m=strcspn(n,".");
	for (i=0;i<m;i++) retval+=(n[i]-48)*pow(10,m-i-1);
	return(retval);
}
