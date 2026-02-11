PostGarbageCollectionProcessing(Isolate* isolate,
                                       GlobalHandles* global_handles) {
    if (state_ != Node::PENDING) return false;
    WeakReferenceCallback func = callback();
    if (func == NULL) {
      Release(global_handles);
      return false;
    }
    void* par = parameter();
    state_ = NEAR_DEATH;
    set_parameter(NULL);

    v8::Persistent<v8::Object> object = ToApi<v8::Object>(handle());
    {


      ASSERT(!object_->IsExternalAsciiString() ||
             ExternalAsciiString::cast(object_)->resource() != NULL);
      ASSERT(!object_->IsExternalTwoByteString() ||
             ExternalTwoByteString::cast(object_)->resource() != NULL);

      VMState state(isolate, EXTERNAL);
      func(object, par);
    }


    ASSERT(state_ != NEAR_DEATH);
    return true;
  }
