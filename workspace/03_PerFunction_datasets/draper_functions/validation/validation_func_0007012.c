GListDoubleClick(GList *l,int frommouse,int index) {
    GEvent e;

    e.type = et_controlevent;
    e.w = l->g.base;
    e.u.control.subtype = et_listdoubleclick;
    e.u.control.g = &l->g;
    e.u.control.u.list.from_mouse = frommouse;
    e.u.control.u.list.changed_index = index;
    if ( l->g.handle_controlevent != NULL )
	(l->g.handle_controlevent)(&l->g,&e);
    else
	GDrawPostEvent(&e);
}
