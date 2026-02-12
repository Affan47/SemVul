string GraphConstructor::FindUniqueName(StringPiece original_name) {
  string name(original_name);
  int count = 0;


  while (NameExistsInGraph(name) || (count > 0 && NameExistsInGraphDef(name))) {
    name = strings::StrCat(original_name, "_", ++count);
  }
  return name;
}
