getHeader(const char* data, size_t len){
	size_t i;
	int enter=-1;
	if (data)
		for (i=0;i<len;i++)
			if (data[i]=='\n'){
				if (enter>=0) enter++;
				if (enter>1) return i;
			} else if (data[i]!='\r') enter=0;
	return 0;
}
