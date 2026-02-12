char *getquotedeol(FILE *sfd) {
    char *pt, *str, *end;
    int ch;

    pt = str = malloc(101); end = str+100;
    while ( isspace(ch = nlgetc(sfd)) && ch!='\r' && ch!='\n' );
    while ( ch!='\n' && ch!='\r' && ch!=EOF ) {
	if ( ch=='\\' ) {


	    ch = getc(sfd);
	    if ( ch=='n' ) ch='\n';


	}
	if ( pt>=end ) {
	    pt = realloc(str,end-str+101);
	    end = pt+(end-str)+100;
	    str = pt;
	    pt = end-100;
	}
	*pt++ = ch;
	ch = nlgetc(sfd);
    }
    *pt='\0';


    if ( !utf8_valid(str) ) {
	pt = latin1_2_utf8_copy(str);
	free(str);
	str = pt;
    }
return( str );
}
