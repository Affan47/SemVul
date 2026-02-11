onKeyRelease(FXObject*,FXSelector sel,void* ptr){
  if(isEnabled()){
    FXTRACE((200,"%s::onKeyRelease %p keysym=0x%04x state=%04x\n",getClassName(),this,((FXEvent*)ptr)->code,((FXEvent*)ptr)->state));
    if(target && target->tryHandle(this,FXSEL(SEL_KEYRELEASE,message),ptr)) return 1;
    if(pane && pane->shown() && pane->handle(pane,sel,ptr)) return 1;
    }
  return 0;
  }
