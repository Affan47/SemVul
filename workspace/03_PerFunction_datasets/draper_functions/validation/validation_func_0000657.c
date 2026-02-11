dispsignal(sig, width, fp)
int sig, width;
XFILE *fp;
{
	int i;

	for (i = 0; signallist[i].sig >= 0; i++)
		if (sig == signallist[i].sig) break;
	if (signallist[i].sig < 0) {
		if ((width -= strsize("Signal ")) < 0) width = 0;
		VOID_C Xfprintf(fp, "Signal %-*d", width, sig);
	}
	else if (!signallist[i].mes || !*(signallist[i].mes)) ;
	else if (!width) Xfputs(signallist[i].mes, fp);
	else VOID_C Xfprintf(fp, "%-*.*s", width, width, signallist[i].mes);
}
