DrawLRTrap(GWindow gw,GRect *pos,int inset,int width,Color col) {
    GPoint pts[5];

    --width;
    if ( width==0 ) {
	GDrawDrawLine(gw,pos->x+pos->width-1-inset,pos->y+pos->height/2,pos->x+pos->width/2,pos->y+pos->height-1-inset,col);
    } else {
	pts[0].x = pos->x+pos->width-1-inset;
		pts[0].y = pos->y+pos->height/2;
	pts[1].x = pts[0].x-width;
		pts[1].y = pts[0].y;
	pts[2].x = pos->x+pos->width/2;
		pts[2].y = pos->y+pos->height-1-inset-width;
	pts[3].x = pts[2].x;
		pts[3].y = pts[2].y+width;
	pts[4] = pts[0];
	GDrawFillPoly(gw,pts,5,col);
    }
}
