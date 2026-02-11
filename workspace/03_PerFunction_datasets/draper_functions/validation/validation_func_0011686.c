g2_X11_ink(int pid, void *pdp,
	       double red, double green, double blue)
{
    g2_X11_device *xout=&g2_X11_dev[pid];
    XColor color;

    color.flags=DoRed|DoGreen|DoBlue;
    color.red   = (int)(red   * USHRT_MAX);
    color.green = (int)(green * USHRT_MAX);
    color.blue  = (int)(blue  * USHRT_MAX);
    if(XAllocColor(xout->display,xout->colormap,&color)) {
	xout->NofInks++;
	if(xout->inks==NULL)
	    xout->inks=
	      (unsigned long *)g2_malloc(xout->NofInks*sizeof(unsigned long));
	else
	    xout->inks=
	      (unsigned long *)g2_realloc((void *)xout->inks,
					  xout->NofInks*sizeof(unsigned long));
	if(xout->inks==NULL) {
	    fputs("g2: not enough memory\n",stderr);
	    return -1;
	}
	xout->inks[xout->NofInks-1]=color.pixel;
	return xout->NofInks-1;
    } else {
	fputs("g2: color is not available\n",stderr);
	return -1;
    }
}
