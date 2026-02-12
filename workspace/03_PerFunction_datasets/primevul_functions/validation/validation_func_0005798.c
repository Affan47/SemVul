void WebContents::Focus() {


#if defined(OS_MACOSX) || defined(OS_LINUX)
  if (owner_window())
    owner_window()->Focus(true);
#endif
  web_contents()->Focus();
}
