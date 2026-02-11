xescapifychar(unsigned int c, int quote, Bytebuffer* s)
{
    if(c >= ' ' && c < '\177') {
	char* p;
	char** q;
	for(p=printescapable,q=printescape;*p;p++,q++) {if(c==*p) break;}
	if(*p) {
	    bbAppend(s,'&');
	    bbCat(s,*q);
	    bbAppend(s,';');
	} else
	    bbAppend(s,(char)c);
    } else {

	    unsigned int hex1 = (c & 0x0f);
	    unsigned int hex2 = ((c >> 4) & 0x0f);
	    bbCat(s,"&#");
	    bbAppend(s,hexdigits[hex2]);
	    bbAppend(s,hexdigits[hex1]);
	    bbAppend(s,';');
    }
}
