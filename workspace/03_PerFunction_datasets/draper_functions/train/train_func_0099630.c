getMinRowHeight(FXint r) const {
  register FXTableItem *item;
  register FXint h,c,t;
  if(r<0 || r>=nrows){ fxerror("%s::getMinRowHeight: row out of range\n",getClassName()); }
  for(c=0,h=0; c<ncols; c++){
    item=cells[r*ncols+c];
    if(item && (r==0 || cells[(r-1)*ncols+c]!=item) && (r==nrows-1 || cells[(r+1)*ncols+c]!=item)){
      t=item->getHeight(this);
      if(t>h) h=t;
      }
    }
  return h;
  }
