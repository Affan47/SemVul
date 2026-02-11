onHeaderResize(FXObject*,FXSelector,void* ptr){
  register FXint hi=(FXint)(FXival)ptr;
  register FXint i,iw,tw,w,nw=0;
  FXString text;


  if(!(options&(ICONLIST_MINI_ICONS|ICONLIST_BIG_ICONS))){
    for(i=0; i<items.no(); i++){
      w=0;


      if(hi==0){
        if(items[i]->miniIcon){
          iw=items[i]->miniIcon->getWidth();
          w+=iw+DETAIL_TEXT_SPACING+SIDE_SPACING/2;
          }
        }


      text=items[i]->label.section('\t',hi);
      if(!text.empty()){
        tw=font->getTextWidth(text.text(),text.length());
        w+=tw+SIDE_SPACING+2;
        }


      if(w>nw) nw=w;
      }


    if(nw>0 && nw!=header->getItemSize(hi)){
      header->setItemSize(hi,nw);
      flags&=~FLAG_RECALC;
      }
    }
  return 1;
  }
