af_hasmeta(const char *infile)
{

    for(const char *cc = infile;*cc;cc++){
	switch(*cc){
	case '?': return 1;
	case '*': return 1;
	case '&': return 1;
	case '`': return 1;
	case '(': return 1;
	case ')': return 1;
	}
    }
    return 0;
}
