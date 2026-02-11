fillArc(FXint x,FXint y,FXint w,FXint h,FXint ang1,FXint ang2){
  if(!surface){ fxerror("FXDCWindow::fillArc: DC not connected to drawable.\n"); }
  XFillArc(DISPLAY(getApp()),surface->id(),(GC)ctx,x,y,w,h,ang1,ang2);
  }
