inputf(fname, newbuf)
register char *fname;
bool newbuf;
{
    FILE *f;
    int fsize,
	rc;

    if (newbuf)
	readonly = NO;

    zerostack(&undo);

    if ( newbuf ) {
	modified = NO;
	low = 0;
    }
    else {
	fixupline(bseekeol(curr));
    }

    printch('"');
    prints(fname);
    prints("\" ");
    if ((f=fopen(fname, "r")) == NULL) {
	prints("[No such file]");
	fsize = 0;
	if (newbuf)
	    newfile = YES;
    }
    else {
	rc = insertfile(f, !newbuf, low, &fsize);
	fclose(f);

	if ( rc > 0 )
	    plural(fsize, " byte");
	else if ( rc < 0 )
	    prints("[read error]");
	else {
	    prints("[overflow]");
	    readonly=1;
	}
	if (newbuf) newfile = NO;
    }
    if (newbuf) {
	fillchar(contexts, sizeof(contexts), -1);
	bufmax = fsize;
    }
    if (*startcmd) {
	count = 1;
	if (*findparse(startcmd,&curr,low) != 0 || curr < 0)
	    curr = low;
	*startcmd = 0;
    }
    else
	curr = low;
}
