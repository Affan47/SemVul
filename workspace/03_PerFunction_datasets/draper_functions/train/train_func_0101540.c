GetConstructorDelegate(Handle<Object> object) {
  ASSERT(!object->IsJSFunction());


  if (object->IsHeapObject() &&
      HeapObject::cast(*object)->map()->has_instance_call_handler()) {
    return Handle<JSFunction>(
        Top::global_context()->call_as_constructor_delegate());
  }

  return Factory::undefined_value();
}
