static void SFDDumpHintMask(FILE *sfd,HintMask *hintmask) {
    unsigned i, j;

    for ( i=HntMax/8-1; i>0; --i )
	if ( (*hintmask)[i]!=0 )
    break;
    for ( j=0;  ; ++j ) {
	if ( ((*hintmask)[j]>>4)<10 )
	    putc('0'+((*hintmask)[j]>>4),sfd);
	else
	    putc('a'-10+((*hintmask)[j]>>4),sfd);
	if ( ((*hintmask)[j]&0xf)<10 )
	    putc('0'+((*hintmask)[j]&0xf),sfd);
	else
	    putc('a'-10+((*hintmask)[j]&0xf),sfd);
        if (j == i) break;
    }
}
