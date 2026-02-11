updateTitle(void)
{
  undrawShadow();
  label()->freeze();
  label()->foreground(titleForeground());
  int h=label()->height();
  int w=label()->width();

  label()->font(titleFont());
  MSBoolean doPlacement=MSFalse;
  label()->label(title());
  int ml=label()->columns();
  if (ml==0&&label()->mapped()==MSTrue)
   {
     label()->unmap();
     doPlacement=MSTrue;
   }
  else if (ml>0&&label()->mapped()==MSFalse)
   {
     label()->map();
     doPlacement=MSTrue;
   }
  positionLabel();
  label()->unfreeze();
  if (label()->height()!=h||label()->width()!=w||doPlacement==MSTrue) adjustSize();
  else if (label()->mapped()==MSTrue) label()->redraw();
  drawShadow();
}
