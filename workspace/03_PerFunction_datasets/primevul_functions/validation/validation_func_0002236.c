void JSObject::_snapshotAddEdgesImpl(GCCell *cell, GC *gc, HeapSnapshot &snap) {
  auto *const self = vmcast<JSObject>(cell);


  if (self->parent_) {
    snap.addNamedEdge(
        HeapSnapshot::EdgeType::Property,

        "__proto__",
        gc->getObjectID(self->parent_));
  }

  HiddenClass::forEachPropertyNoAlloc(
      self->clazz_.get(gc->getPointerBase()),
      gc->getPointerBase(),
      [self, gc, &snap](SymbolID id, NamedPropertyDescriptor desc) {
        if (InternalProperty::isInternal(id)) {

          return;
        }

        GCHermesValue &prop =
            namedSlotRef(self, gc->getPointerBase(), desc.slot);
        const llvh::Optional<HeapSnapshot::NodeID> idForProp =
            gc->getSnapshotID(prop);
        if (!idForProp) {
          return;
        }
        std::string propName = gc->convertSymbolToUTF8(id);


        if (auto index = ::hermes::toArrayIndex(propName)) {
          snap.addIndexedEdge(
              HeapSnapshot::EdgeType::Element,
              index.getValue(),
              idForProp.getValue());
        } else {
          snap.addNamedEdge(
              HeapSnapshot::EdgeType::Property, propName, idForProp.getValue());
        }
      });
}
