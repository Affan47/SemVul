loadSettings() {
  bool restoredSettings = false;
  if (opfile) {
    delete opfile;
  }
  opfile = new Options( FN_SETTINGS );
  playerKeys.clear();
  for(int i=0; i < MAX_PLAYER_CNT; ++i) {
    PlayerEventKeys pk;
    for(int t=1; t < PlayerEventCnt; ++t) {
      int key;
      string keyname = string("PLAYER") + asString(i) + "-" + playerEventNames[(PlayerEvent)t];
      if (!opfile->getInt( keyname , key)) {
	key = defaultSettings[ keyname ];
	restoredSettings = true;
      }
      pk[ (PlayerEvent)t ] = (SDLKey)key;
    }
    playerKeys.push_back(pk);
  }
  if (restoredSettings) {
    saveSettings();
  }
}
