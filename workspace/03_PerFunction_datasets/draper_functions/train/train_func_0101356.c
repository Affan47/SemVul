onPaint(FXObject*,FXSelector,void* ptr){
  FXEvent *ev=(FXEvent*)ptr;
  FXDCWindow dc(canvas,ev);
  dc.setForeground(canvas->getBackColor());
  dc.fillRectangle(ev->rect.x,ev->rect.y,ev->rect.w,ev->rect.h);
  return 1;
  }
