selectzoom_cb(Fl_Object *, void *)
{
    static char  currzoomtxt[100];

    sprintf(currzoomtxt, "%f", (double)(mainViewer->zoomFactor()));

    const char *zoomtxt = fl_input("Enter zoom factor", currzoomtxt);
    double newzoom = (zoomtxt != 0) ? atof(zoomtxt):mainViewer->zoomFactor();


    if (newzoom > 0)
	mainViewer->zoomFactor(newzoom);
    else
	errprintf("Zoom factor must be strictly positive\n");

    return;
}
