showHiddenFiles(FXbool showing){
  FXuint opts=options;
  if(showing) opts|=DIRLIST_SHOWHIDDEN; else opts&=~DIRLIST_SHOWHIDDEN;
  if(opts!=options){
    options=opts;
    scan(TRUE);
    }
  }
