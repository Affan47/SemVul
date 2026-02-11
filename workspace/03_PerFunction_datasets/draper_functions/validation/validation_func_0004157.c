create() {
  FXTopWindow::create();
  if (xid) {
    Atom xembedinfo = XInternAtom((Display*)getApp()->getDisplay(),"_XEMBED_INFO",0);
    if (xembedinfo!=None) {
      unsigned long info[2]={0,(1<<0)};
      XChangeProperty((Display*)getApp()->getDisplay(),xid,xembedinfo,xembedinfo,32,PropModeReplace,(unsigned char*)info,2);
      }
    }
  }
