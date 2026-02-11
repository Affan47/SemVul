GListBSelectOne(GGadget *g, int32 pos) {
    GListButton *gl = (GListButton *) g;
    int i;

    for ( i=0; i<gl->ltot; ++i )
	gl->ti[i]->selected = false;
    if ( pos>=gl->ltot ) pos = gl->ltot-1;
    if ( pos<0 ) pos = 0;
    if ( gl->ltot>0 ) {
	gl->ti[pos]->selected = true;
	GButtonSetImageTitle(g,gl->ti[pos]->image,gl->ti[pos]->text,gl->ti[pos]->image_precedes);
    }
}
