updateColumnNumbers(FXint lo,FXint hi){
  FXString label;
  for(FXint c=lo; c<hi; c++){
    setColumnText(c,label.format("%u",c+1));
    }
  }
