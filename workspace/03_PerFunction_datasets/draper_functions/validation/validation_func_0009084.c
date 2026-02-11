OnDraw(wxDC &dc)
{
	int  x, y, x2, y2, ix;
	int  width, height;
	double xscale, yscale;

	if(show_spectrum) DrawSpectrum(dc);

	if(npoints==0) return;

	GetClientSize(&width,&height);

	xscale = double(width) / npoints;
	yscale = double(height) / 256.0;

	if(npoints > 8)
	{

		dc.SetPen(*wxMEDIUM_GREY_PEN);
		x = 0;
		y = height - int(graph[0]*yscale);
		for(ix=1; ix<npoints; ix++)
		{
			dc.DrawLine(x,y,x2=int(ix*xscale),y2=height - int(graph[ix]*yscale));
			x = x2;
			y = y2;
		}
	}
}
