button1Press(const XEvent *event_)
{
  MSBoolean focus=MSTrue;
  if (acceptFocus()==MSTrue) focus=traverseFocus(this);
  if (focus==MSTrue&&doubleClick().isDoubleClick(event_)==MSTrue) doubleClickNotify();
  else buttonSelectionNotify();
}
