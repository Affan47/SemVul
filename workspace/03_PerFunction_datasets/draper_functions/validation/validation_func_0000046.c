onMiddleBtnPress(FXObject*,FXSelector,void* ptr){
  FXEvent *event=(FXEvent*)ptr;
  register FXint p=pos;
  register int travel,lo,hi,t;
  if(isEnabled()){
    grab();
    getApp()->removeTimeout(this,ID_TIMEWHEEL);
    getApp()->removeTimeout(this,ID_AUTOSCROLL);
    if(target && target->tryHandle(this,FXSEL(SEL_MIDDLEBUTTONPRESS,message),ptr)) return 1;
    mode=MODE_DRAG;
    flags&=~FLAG_UPDATE;
    dragpoint=thumbsize/2;
    if(options&SCROLLBAR_HORIZONTAL){
      travel=width-height-height-thumbsize;
      t=event->win_x-dragpoint;
      if(t<height) t=height;
      if(t>(width-height-thumbsize)) t=width-height-thumbsize;
      if(t!=thumbpos){
        FXMINMAX(lo,hi,t,thumbpos);
        update(lo,0,hi+thumbsize-lo,height);
        thumbpos=t;
        }
      if(travel>0){ p=(FXint)((((FXdouble)(thumbpos-height))*(range-page))/travel); } else { p=0; }
      }
    else{
      travel=height-width-width-thumbsize;
      t=event->win_y-dragpoint;
      if(t<width) t=width;
      if(t>(height-width-thumbsize)) t=height-width-thumbsize;
      if(t!=thumbpos){
        FXMINMAX(lo,hi,t,thumbpos);
        update(0,lo,width,hi+thumbsize-lo);
        thumbpos=t;
        }
      if(travel>0){ p=(FXint)((((FXdouble)(thumbpos-width))*(range-page))/travel); } else { p=0; }
      }
    if(p<0) p=0;
    if(p>(range-page)) p=range-page;
    if(pos!=p){
      pos=p;
      flags|=FLAG_CHANGED;
      if(target) target->tryHandle(this,FXSEL(SEL_CHANGED,message),(void*)(FXival)pos);
      }
    return 1;
    }
  return 0;
  }
