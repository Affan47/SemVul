_GME_Down(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_buttonactivate ) {
	GMatrixEditDown( g->data );
    }
return( true );
}
