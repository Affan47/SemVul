SetPrototype(Object* value,
                                    bool skip_hidden_prototypes) {


  if (!value->IsJSObject() && !value->IsNull()) return value;


  for (Object* pt = value; pt != Heap::null_value(); pt = pt->GetPrototype()) {
    if (JSObject::cast(pt) == this) {

      HandleScope scope;
      return Top::Throw(*Factory::NewError("cyclic_proto",
                                           HandleVector<Object>(NULL, 0)));
    }
  }

  JSObject* real_receiver = this;

  if (skip_hidden_prototypes) {


    Object* current_proto = real_receiver->GetPrototype();
    while (current_proto->IsJSObject() &&
          JSObject::cast(current_proto)->map()->is_hidden_prototype()) {
      real_receiver = JSObject::cast(current_proto);
      current_proto = current_proto->GetPrototype();
    }
  }


  Object* new_map;
  { MaybeObject* maybe_new_map = real_receiver->map()->CopyDropTransitions();
    if (!maybe_new_map->ToObject(&new_map)) return maybe_new_map;
  }
  Map::cast(new_map)->set_prototype(value);
  real_receiver->set_map(Map::cast(new_map));

  Heap::ClearInstanceofCache();

  return value;
}
