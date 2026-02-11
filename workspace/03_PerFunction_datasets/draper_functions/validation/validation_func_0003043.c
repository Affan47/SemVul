load(FXStream& store){
  FXWindow *child=NULL;
  FXDrawable::load(store);
  getApp()->windowCount++;
  store >> child;
  while(child){
    child->parent=this;
    child->owner=this;
    child->prev=last;
    child->next=NULL;
    if(last){
      last->next=child;
      }
    else{
      first=child;
      }
    last=child;
    store >> child;
    }
  store >> accelTable;
  store >> defaultCursor;
  store >> dragCursor;
  store >> target;
  store >> message;
  store >> xpos;
  store >> ypos;
  store >> backColor;
  store >> tag;
  store >> options;
  store >> flags;
  store >> wk;
  }
