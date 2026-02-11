control_dir(const char* name,bool indir) {
  std::list<DirectAccess>::iterator i;
  for(i=access.begin();i!=access.end();++i) {
    if(i->belongs(name,indir)) break;
  };
  return i;
}
