lsplit(char** string_ref, char delim1, char delim2, char encloser) {
	lsplit_result result;

	if(char* string=*string_ref) {
		if(encloser && *string==encloser) {
			string++;

			char *read;
			char *write;
			write=read=string;
			char c;

			while(c=*read++) {
				if(c==encloser) {
					if(*read==encloser)
						read++;
					else
						break;
				}
				*write++=c;
			}

			while(c=*read++) {
				if(c==delim1 || c==delim2) {
					result.delim=c;
					break;
				} else 	if(c!=encloser)
					*write++=c;
			}
			*write=0;
			*string_ref=c? read: 0;
			result.piece=string;
			return result;
		} else
			return lsplit(string_ref, delim1, delim2);
	}
	result.piece=0;
	return result;
}
