writeColorEntry(const FXchar *section,const FXchar *key,FXColor val){
  if(!section || !section[0]){ fxerror("FXSettings::writeColorEntry: bad section argument.\n"); }
  if(!key || !key[0]){ fxerror("FXSettings::writeColorEntry: bad key argument.\n"); }
  FXStringDict *group=insert(section);
  if(group){
    FXchar buffer[64];
    group->replace(key,fxnamefromcolor(buffer,val),TRUE);
    modified=true;
    return true;
    }
  return false;
  }
