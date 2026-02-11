eraseCursorOverhang(){
  register FXint xx,yt,yb,fh;
  FXASSERT(0<=cursorpos && cursorpos<=length);
  FXASSERT(0<=cursorrow && cursorrow<=nrows);
  if(toprow<=cursorrow && cursorrow<toprow+nvisrows){
    xx=pos_x+marginleft+barwidth+lineWidth(cursorstart,cursorpos-cursorstart)-1;
    if(barwidth<=xx+3 && xx-2<viewport_w){
      FXDCWindow dc(this);
      fh=font->getFontHeight();
      yt=pos_y+margintop+cursorrow*fh;
      yb=yt+fh-1;
      dc.setClipRectangle(barwidth,0,viewport_w-barwidth,viewport_h);
      if(xx-2<=marginleft+barwidth && barwidth<=xx+3){
        dc.setForeground(backColor);
        dc.fillRectangle(barwidth,yt,marginleft,fh);
        }
      if(viewport_w-marginright<=xx+3 && xx-2<=viewport_w){
        dc.setForeground(backColor);
        dc.fillRectangle(viewport_w-marginright,yt,marginright,fh);
        }
      if(yt<=margintop && 0<=yb){
        dc.setForeground(backColor);
        dc.fillRectangle(xx-2,0,5,margintop);
        }
      if(viewport_h-marginbottom<=yb && yt<viewport_h){
        dc.setForeground(backColor);
        dc.fillRectangle(xx-2,viewport_h-marginbottom,5,marginbottom);
        }
      }
    }
  }
