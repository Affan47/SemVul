CaptureAllWindows(void)
{
  int i,j;
  unsigned int nchildren;
  Window root, parent, *children;

  PPosOverride = TRUE;

  if(!XQueryTree(dpy, Scr.Root, &root, &parent, &children, &nchildren))
    return;


  for (i = 0; i < nchildren; i++)
    {
      if (children[i])
	{
	  XWMHints *wmhintsp = XGetWMHints (dpy, children[i]);
	  if (wmhintsp)
	    {
	      if (wmhintsp->flags & IconWindowHint)
		{
		  for (j = 0; j < nchildren; j++)
		    {
		      if (children[j] == wmhintsp->icon_window)
			{
			  children[j] = None;
			  break;
			}
		    }
		}
	      XFree ((char *) wmhintsp);
	    }
	}
    }


  for (i = 0; i < nchildren; i++)
    {
      if (children[i] && MappedNotOverride(children[i]))
	{
	  XUnmapWindow(dpy, children[i]);
	  Event.xmaprequest.window = children[i];
	  HandleMapRequest ();
	}
    }

  isIconicState = DontCareState;

  if(nchildren > 0)
    XFree((char *)children);


  PPosOverride = FALSE;
}
