GTabSetChanged(GTabSet *gts,int oldsel) {
    GEvent e;

    e.type = et_controlevent;
    e.w = gts->g.base;
    e.u.control.subtype = et_radiochanged;
    e.u.control.g = &gts->g;
    if ( gts->g.handle_controlevent != NULL )
	(gts->g.handle_controlevent)(&gts->g,&e);
    else
	GDrawPostEvent(&e);
}
