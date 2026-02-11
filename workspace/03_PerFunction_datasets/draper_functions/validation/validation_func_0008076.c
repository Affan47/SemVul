XpTableGetProposedChildSize(  tw )
    XpTableWidget	tw;
{
    int		width, height, bw, x, y;
    XpTableLoc  loc = tw->table.real_layout;

    while ( loc->w && loc->w != tw->table.resize_child )
	++loc;

    if ( loc->w != tw->table.resize_child )
    {
	String args[3];
	Cardinal two = 2;
	args[0] = XtName(tw->table.resize_child);
	args[1] = XtName((Widget)tw);
	args[2] = NULL;
	XtWarningMsg( "unmanagedChildMadeResizeRequest",
		      "XpTableGetProposedChildSize",
		      "Xt Implementation Bug",
		      "XtMakeGeometryRequest passed request from unmanaged child %s to table %s\n",
		      args, &two );

	XpTableForgetProposedLayout(  tw );
	return;
    }


    width = height = 0;
    bw = tw->table.resize_border_width;

    XpTableComputeChildSize(  tw, loc, &width, &height, &bw, &x, &y );

    if ( 1 < width &&  1 < height )
    {
	XpTableApproveGeometryChanges(  tw, loc->w, width, height, bw );
	return;
    }


    width = height = 0;
    bw = loc->w->core.border_width;

    XpTableComputeChildSize(  tw, loc, &width, &height, &bw, &x, &y );

    if ( width  < 1 ) width  = 1;
    if ( height < 1 ) height = 1;
    XpTableApproveGeometryChanges(  tw, loc->w, width, height, bw );
}
