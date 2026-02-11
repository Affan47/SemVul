ImgInit(wp, closure)
ChimeraSink wp;
void *closure;
{
  HTMLInline isp = (HTMLInline)closure;
  ChimeraRenderHooks *rh;
  char *ctype;

  ctype = SinkGetInfo(wp, "content-type");
  if ((rh = RenderGetHooks(SinkToResources(wp), ctype)) == NULL)
  {
    SinkCancel(wp);
    InlineContinue(isp);
    return(-1);
  }

  isp->wd = GUICreate(isp->li->wc, isp->li->wd, InlineResizeCallback, isp);
  if (isp->width > 0 && isp->height > 0)
  {
    GUISetInitialDimensions(isp->wd, isp->width, isp->height);
  }
  if (isp->setupcalled)
  {
    GUIMap(isp->wd, isp->box->x + isp->hspace, isp->box->y + isp->vspace);
  }

  isp->wn = RenderCreate(isp->li->wc, isp->wd, isp->wp,
			 rh, &(isp->orh), isp->rc, NULL,
			 NULL, NULL);
  if (isp->wn == NULL)
  {
    SinkCancel(wp);
    return(-1);
  }

  return(0);
}
