GetXPM(void)
{
  view.attributes.valuemask |= XpmReturnPixels;
  view.attributes.valuemask |= XpmReturnExtensions;

  if(XpmCreatePixmapFromData(dpy, Root, fvwm2_xpm,
			     &view.pixmap, &view.mask,
			     &view.attributes)!=XpmSuccess)
    exit(1);
}
