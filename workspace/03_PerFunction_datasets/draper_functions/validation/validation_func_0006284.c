inf_gtk_browser_view_find_sync(InfGtkBrowserView* view,
                               InfGtkBrowserViewBrowser* view_browser,
                               InfcSessionProxy* proxy)
{
  GSList* item;
  InfGtkBrowserViewSync* sync;

  for(item = view_browser->syncs; item != NULL; item = item->next)
  {
    sync = (InfGtkBrowserViewSync*)item->data;
    if(sync->proxy == proxy)
      return sync;
  }

  return NULL;
}
