refresh()
{
  int res = noutrefresh();
  if (res==OK && (static_cast<NCursesWindow*>(0) != viewWin)) {
    res = (viewWin->refresh());
  }
  return(res);
}
