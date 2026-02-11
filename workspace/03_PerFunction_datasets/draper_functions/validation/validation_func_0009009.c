drawRightArrow(FXDCWindow& dc,FXint x,FXint y){
  FXPoint points[3];
  points[0].x=x-ARROWLENGTH+1;
  points[0].y=y-ARROWLENGTH;
  points[1].x=x-ARROWLENGTH+1;
  points[1].y=y+ARROWLENGTH;
  points[2].x=x+1;
  points[2].y=y;
  dc.fillPolygon(points,3);
  }
