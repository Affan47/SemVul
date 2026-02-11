expand_backslashes(SgrepData *sgrep,const char *s) {
    int i=0;
    SgrepString *r;
    const unsigned char *str=(const unsigned char *)s;

    r=new_string(sgrep,strlen(s));
    while(str[i]) {
	if (str[i]=='\\') {
	    int ch;
	    i++;
	    ch=expand_backslash_escape(sgrep,str,&i);
	    if (ch>=0) string_push(r,ch);
	} else {
	    string_push(r,str[i]);
	    i++;
	}
    }
    return r;
}
