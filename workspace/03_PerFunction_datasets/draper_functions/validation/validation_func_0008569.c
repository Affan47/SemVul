setinput(int fh, int mode, char *name) {

    inname=name;
    inspecial=NULL;
    ibl=0;
    icnt=0;
    infile=fh;
    r_crc=mode&CRCCALC;
    if (r_crc) {
	if (!crctabok) makecrctab();
	crc=CRCMASK;
    }
    r_progdisp=mode&PROGDISP;
}
