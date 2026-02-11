GetIndexedPropertiesExternalArrayData() {
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  ON_BAILOUT(self->GetIsolate(),
             "v8::GetIndexedPropertiesExternalArrayData()",
             return NULL);
  if (self->HasExternalArrayElements()) {
    return i::ExternalArray::cast(self->elements())->external_pointer();
  } else {
    return NULL;
  }
}
