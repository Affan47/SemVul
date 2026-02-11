CloseAllWindows( void ) {
  for ( Window *w = static_cast<Window *>(windows.Head());
        w && !w->Closed(); w = static_cast<Window *>(w->Next()) )
    w->Close();
  Refresh();
}
