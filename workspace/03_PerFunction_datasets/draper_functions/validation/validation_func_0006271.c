Subcode(int level) {
  if(!ver12) return "";
  if(level < 0) return "";
  if(!code) return "";
  XMLNode subcode = code;
  for(;level;--level) {
    subcode=subcode["Subcode"];
    if(!subcode) return "";
  };
  return subcode["Value"];
}
