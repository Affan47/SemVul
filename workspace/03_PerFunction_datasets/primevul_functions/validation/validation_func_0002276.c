std::string JSObject::getNameIfExists(PointerBase *base) {

  if (auto nameVal = tryGetNamedNoAlloc(
          this, base, Predefined::getSymbolID(Predefined::displayName))) {
    if (auto *name = dyn_vmcast<StringPrimitive>(*nameVal)) {
      return converter(name);
    }
  }

  if (auto nameVal = tryGetNamedNoAlloc(
          this, base, Predefined::getSymbolID(Predefined::name))) {
    if (auto *name = dyn_vmcast<StringPrimitive>(*nameVal)) {
      return converter(name);
    }
  }

  return "";
}
