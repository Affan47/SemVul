std::string JSObject::getHeuristicTypeName(GC *gc) {
  PointerBase *const base = gc->getPointerBase();
  if (auto constructorVal = tryGetNamedNoAlloc(
          this, base, Predefined::getSymbolID(Predefined::constructor))) {
    if (auto *constructor = dyn_vmcast<JSObject>(*constructorVal)) {
      auto name = constructor->getNameIfExists(base);


      if (!name.empty() && name != "Object")
        return name;
    }
  }

  std::string name = getVT()->base.snapshotMetaData.defaultNameForNode(this);


  if (getClass(base)->isDictionary()) {
    return name + "(Dictionary)";
  }


  if (getKind() != CellKind::ObjectKind) {
    return name;
  }


  std::vector<std::string> propertyNames;
  HiddenClass::forEachPropertyNoAlloc(
      getClass(base),
      base,
      [gc, &propertyNames](SymbolID id, NamedPropertyDescriptor) {
        if (InternalProperty::isInternal(id)) {

          return;
        }
        propertyNames.emplace_back(gc->convertSymbolToUTF8(id));
      });


  constexpr int kMaxPropertiesForTypeName = 5;
  bool truncated = false;
  if (propertyNames.size() > kMaxPropertiesForTypeName) {
    propertyNames.erase(
        propertyNames.begin() + kMaxPropertiesForTypeName, propertyNames.end());
    truncated = true;
  }

  if (propertyNames.empty()) {

    return name;
  }
  name += "(";
  bool first = true;
  for (const auto &prop : propertyNames) {
    if (!first) {
      name += ", ";
    }
    first = false;
    name += prop;
  }
  if (truncated) {


    static_assert(
        kMaxPropertiesForTypeName >= 1,
        "Property truncation should not happen for 0 properties");
    name += ", ...";
  }
  name += ")";
  return name;
}
