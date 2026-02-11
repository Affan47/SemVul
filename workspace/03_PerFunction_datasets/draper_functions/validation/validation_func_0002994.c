setDefaultCursor(FXCursor* cur){
  if(defaultCursor!=cur){
    if(cur==NULL){ fxerror("%s::setDefaultCursor: NULL cursor argument.\n",getClassName()); }
    if(xid){
      if(cur->id()==0){ fxerror("%s::setDefaultCursor: Cursor has not been created yet.\n",getClassName()); }
#ifndef WIN32
      XDefineCursor(DISPLAY(getApp()),xid,cur->id());
#else
      if(underCursor() && !grabbed()) SetCursor((HCURSOR)cur->id());
#endif
      }
    defaultCursor=cur;
    }
  }
