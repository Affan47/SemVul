create(){
  if(!id()) getApp()->addTimeout(this,ID_REFRESHTIMER,REFRESHINTERVAL);
  FXTreeList::create();
  if(!deleteType){deleteType=getApp()->registerDragType(deleteTypeName);}
  if(!urilistType){urilistType=getApp()->registerDragType(urilistTypeName);}
  open_folder->create();
  closed_folder->create();
  mini_doc->create();
  mini_app->create();
  cdromicon->create();
  harddiskicon->create();
  networkicon->create();
  floppyicon->create();
  zipdiskicon->create();
  scan(FALSE);
  }
