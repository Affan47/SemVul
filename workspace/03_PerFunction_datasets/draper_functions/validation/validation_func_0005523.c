setListStyle(FXuint mode){
  FXuint opts=(options&~TREELISTBOX_MASK)|(mode&TREELISTBOX_MASK);
  if(opts!=options){
    options=opts;
    recalc();
    }
  }
