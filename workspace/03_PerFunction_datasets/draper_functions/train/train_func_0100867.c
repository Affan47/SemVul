flimage_swapbuffer( FL_IMAGE * im )
{
    int sw = im->sw ? im->sw : im->w,
        sh = im->sh ? im->sh : im->h;

    XCopyArea(im->xdisplay, im->pixmap, im->win, im->gc,
              im->sx, im->sy, sw, sh, im->wx, im->wy);
    return 0;
}
