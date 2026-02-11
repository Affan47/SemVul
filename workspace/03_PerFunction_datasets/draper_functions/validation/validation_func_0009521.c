free_laser(Display *display, lasersstruct *lp)
{
	if (lp->laser != NULL) {
		(void) free((void *) lp->laser);
		lp->laser = (laserstruct *) NULL;
	}
	if (lp->stippledGC != None) {
		XFreeGC(display, lp->stippledGC);
		lp->stippledGC = None;
	}
}
