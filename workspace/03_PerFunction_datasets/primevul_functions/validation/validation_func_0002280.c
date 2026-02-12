void JSObject::_snapshotAddLocationsImpl(
    GCCell *cell,
    GC *gc,
    HeapSnapshot &snap) {
  auto *const self = vmcast<JSObject>(cell);
  PointerBase *const base = gc->getPointerBase();


  if (auto constructorVal = tryGetNamedNoAlloc(
          self, base, Predefined::getSymbolID(Predefined::constructor))) {
    if (constructorVal->isObject()) {
      if (auto *constructor = dyn_vmcast<JSFunction>(*constructorVal)) {
        constructor->addLocationToSnapshot(snap, gc->getObjectID(self));
      }
    }
  }
}
