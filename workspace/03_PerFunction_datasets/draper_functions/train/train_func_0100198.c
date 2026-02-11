output(char *p)
{
    int i,n;
    char *pp, *pe, *pt;

    pp=strchr(p,'\n');
    for(pp++; *pp; pp=pe) {
	pe=strchr(pp,'\n'); if(pe) *pe++=0; else pe=pp+strlen(pp);
	if(memcmp(pp,ans_str,strlen(ans_str))==0) pp+=strlen(ans_str);
	n=strlen(pp); if(n==0) {
	    puts(""); continue;
	}

	for(i=0;i<n;i++) {
	    if(*(pp+i)=='\n' || *(pp+i)=='\%') *(pp+i)=' ';
	}

	while(isspace(*pp) && pp<pe) pp++;
	pt=pp+strlen(pp)-1;
	while(isspace(*pt) && pt>pp) *pt--=0;
	strip_zeros(pp);
	puts(pp);
    }
}
