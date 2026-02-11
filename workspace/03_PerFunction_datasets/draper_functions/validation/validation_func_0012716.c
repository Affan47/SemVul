doPaint( const QRect& area )
    {
#if 0
    fprintf( stderr, "PAINT: %d,%d-%dx%d\n", area.x(), area.y(), area.width(), area.height());
#endif
    if( window == None )
        return;

    Pixmap pixmap = XCreatePixmap( qt_xdisplay(), DefaultRootWindow( qt_xdisplay()),
        area.width(), area.height(), x11Depth());
    GC gc = qt_xget_temp_gc( x11Screen(), false );

    XCopyArea( qt_xdisplay(), splash_pixmap, pixmap, gc,
        area.x(), area.y(), area.width(), area.height(), 0, 0 );

    for( int i = 0;
         i < MAX_ITEMS;
         ++i )
        {
        AnimData* anim = animations[ i ];
        PixmapData* frame = anim != NULL ? &anim->frames[ anim->current_frame ] : NULL;
        if( anim != NULL
            && area.intersects( QRect( anim->x, anim->y, frame->w, frame->h )))
            {
            XCopyArea( qt_xdisplay(), frame->hd, pixmap, gc,
                qMax( 0, area.x() - anim->x ), qMax( 0, area.y() - anim->y ),
                area.x() - anim->x + area.width(), area.y() - anim->y + area.height(),
                qMax( 0, anim->x - area.x()), qMax( 0, anim->y - area.y()));
            }
        }
    XCopyArea( qt_xdisplay(), pixmap, window, gc, 0, 0, area.width(), area.height(), area.x(), area.y());
    XFreePixmap( qt_xdisplay(), pixmap );
    }
