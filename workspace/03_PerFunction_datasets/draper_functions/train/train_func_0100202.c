usage(char *prog)
{
    char *h;

    if (NULL != (h = strrchr(prog,'/')))
	prog = h+1;
    fprintf(stderr,
	    "\n"
	    "%s shows contents of RIFF files (AVI,WAVE...).\n"
	    "(c) 1994 UP-Vision Computergrafik for c't\n"
	    "unix port and some extensions (for avi) by Gerd Knorr\n"
	    "\n"
	    "usage:  %s [ -j ] [ -e ] filename\n"
	    "options:\n"
	    "  -j  try to decode some mjpeg headers\n"
	    "  -e  don't stop on errors\n"
	    "\n",
	    prog,prog);
}
