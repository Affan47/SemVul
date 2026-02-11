gm_colorize_bitmap(FXImage * icon,FXColor nc) {
  FXColor color;
  for (FXint y=0;y<icon->getHeight();y++){
    for (FXint x=0;x<icon->getWidth();x++){
      color=icon->getPixel(x,y);
      if (FXALPHAVAL(color)>0) {
        icon->setPixel(x,y,FXRGBA(FXREDVAL(nc),FXGREENVAL(nc),FXBLUEVAL(nc),FXALPHAVAL(color)));
        }
      }
    }
  }
