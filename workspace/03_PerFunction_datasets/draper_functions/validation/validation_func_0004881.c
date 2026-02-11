getName(Value *V) {
  StringRef Name = V->getName();
  if (Name.startswith("\1"))
    return Name.substr(1);
  return Name;
}
