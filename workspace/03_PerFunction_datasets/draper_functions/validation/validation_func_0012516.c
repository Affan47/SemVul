do_chasen_standalone(FILE * ifp, FILE * ofp)
{
    int istty;


    istty = ofp == stdout && isatty(fileno(stdout));

    if (is_partial) {
	chasen_parse_segments(ifp, ofp);
    } else {
	while (!chasen_fparse(ifp, ofp))
	    if (!istty)
		fflush(ofp);
    }
}
