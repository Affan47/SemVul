init(GMSource * src) {
  FXASSERT(source==NULL);
  FXASSERT(src);

  source=src;


  columns.clear();
  source->configure(columns);

  loadSettings(source->settingKey());

  clear();

  if (source) {
    if (browsersplit->getExpanded()==SHOWBROWSER) {
      listGenres();
      initSelection(genrelist,"genre-list-selection",source->settingKey());
      listArtists();
      initSelection(artistlist,"artist-list-selection",source->settingKey());
      listAlbums();
      initSelection(albumlist,"album-list-selection",source->settingKey());
      listTracks();
      }
    else {
      listTracks();
      }

    FXint active =  getApp()->reg().readIntEntry("window","track-list-current",-1);
    if (active>=0 && active<tracklist->getNumItems()) {
      tracklist->setCurrentItem(active);
      tracklist->selectItem(active);
      }
    tracklist->setPosition(tracklist_posx,tracklist_posy);
    }
  }
