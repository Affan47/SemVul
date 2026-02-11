saveTrackSettings(const FXString & key) const {
  tracklist->saveHeaders();
  FXString browseprefix = (browsersplit->getExpanded()==SHOWBROWSER) ? "browse" : "list";
  FXString name;
  for (FXint i=0;i<columns.no();i++){
    name = columns[i].name;
    getApp()->reg().writeBoolEntry(key.text(),FXString(browseprefix+"-showcolumn-"+name.lower()).text(),columns[i].show);
    getApp()->reg().writeIntEntry(key.text(),FXString(browseprefix+"-columnwidth-"+name.lower()).text(),columns[i].size);
    getApp()->reg().writeIntEntry(key.text(),FXString(browseprefix+"-columnindex-"+name.lower()).text(),columns[i].index);
    }
  getApp()->reg().writeIntEntry(key.text(),FXString(browseprefix+"-sort-column").text(),tracklist->getSortMethod());
  getApp()->reg().writeBoolEntry(key.text(),FXString(browseprefix+"-sort-reverse").text(),getSortReverse());
#if FOXVERSION < FXVERSION(1,7,0)
  getApp()->reg().writeUnsignedEntry(key.text(),FXString(browseprefix+"-sort-seed").text(),sort_seed);
#else
  getApp()->reg().writeUIntEntry(key.text(),FXString(browseprefix+"-sort-seed").text(),sort_seed);
#endif
  }
