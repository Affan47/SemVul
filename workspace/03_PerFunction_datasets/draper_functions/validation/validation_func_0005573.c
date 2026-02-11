GGadgetSetTitle8WithMn(GGadget *g,const char *title) {
    char *pt = strchr(title,'_');
    char *freeme=NULL;
    int mnc;

    if ( pt!=NULL ) {
	char *pos = pt+1;
	mnc = utf8_ildb((const char **) &pos);
	g->mnemonic = mnc;
	freeme = copy(title);
	for ( pt = freeme + (pt-title); *pt; ++pt )
	    *pt = pt[1];
	title = freeme;
    } else
	g->mnemonic = 0;
    GGadgetSetTitle8(g,title);
    free(freeme);
}
