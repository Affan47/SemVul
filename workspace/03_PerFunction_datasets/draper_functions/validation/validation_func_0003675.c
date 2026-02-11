selectionClear(const XEvent *)
{
  _server->copyBuffer("Selection Cleared");
  activateCallback(MSWidgetCallback::selectionclear);
}
