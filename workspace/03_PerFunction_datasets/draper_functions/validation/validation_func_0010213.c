DrawRightArrowTab(GWindow pixmap, GTabSet *gts, int x, int y ) {
    Color fg = gts->g.box->main_foreground;
    GPoint pts[5];
    int retx = x + gts->arrow_width, cnt;

    if ( fg==COLOR_DEFAULT ) fg = GDrawGetDefaultForeground(GDrawGetDisplayOfWindow(pixmap));
    GBoxDrawTabOutline(pixmap,&gts->g,x,y,gts->arrow_width,gts->rowh,false);
    gts->hasrarrow = true;
	y += (gts->rowh-gts->arrow_size)/2;
	x += (gts->arrow_width-gts->arrow_size/2)/2;
	cnt = 4;
	pts[0].y = (y+(gts->arrow_size-1)/2); 	pts[0].x = x + (gts->arrow_size-1)/2;
	pts[1].y = y; 				pts[1].x = x;
	pts[2].y = y+gts->arrow_size-1; 	pts[2].x = pts[1].x;
	pts[3] = pts[0];
	if ( !(gts->arrow_size&1 )) {
	    ++pts[3].y;
	    pts[4] = pts[0];
	    cnt = 5;
	}
	GDrawFillPoly(pixmap,pts,cnt,fg);
return( retx );
}
