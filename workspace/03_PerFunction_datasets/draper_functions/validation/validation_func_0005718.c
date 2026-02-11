dact_ui_update(void) {
	static int drawing=0;
	float done;
	char *bar1, *bar2, *clean="";
	int width=80,percent;

	if (!dact_ui_getopt(DACT_UI_OPT_LEVEL)) return;
	percent=dact_ui_getopt(DACT_UI_OPT_PERCENT);

	if (getenv("COLUMNS")!=NULL) width=atoi(getenv("COLUMNS"));
	if (width<10) return;
	width=(width>30?10:5);

	if (percent>100) percent=100;
	if (percent>-1) {
		done=(((float) width)*(((float) percent)/100));

		bar1=malloc((int) done+2);
		bar2=malloc((int) (width-done)+3);
		memset(bar1,'#',(int) done);
		memset(bar2,'.',(int) (width-done+0.9999999));
		bar1[(int) done]=0;
		bar2[(int) (width-done+0.9999999)]=0;
	} else {
		bar2=malloc(width+1);
		memset(bar2,'?',width);
		bar2[width]=0;
		bar1=bar2+width;
		percent=0;
	}
	if (dact_ui_getopt(DACT_UI_OPT_COLOR)) {
		fprintf(stderr, "=> \033[1;30m[\033[1;32m%s\033[1;37m%s\033[1;30m] \033[1;37m%03i\033[0;31m%%\033[0m",bar1,bar2,percent);
		clean="\033[K";
	} else {
		fprintf(stderr, "=> [%s%s] %3i%%",bar1,bar2,percent);
	}
	fprintf(stderr, " [%c] | Status: %s%s\r",*("|/-\\"+(drawing&3)),dact_ui_statusvar, clean);
	fflush(stderr);

	free(bar2);
	if (bar1!=(bar2+width)) free(bar1);

	drawing++;
	return;
}
