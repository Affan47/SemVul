PrintFunction(Object* f, Object* receiver, Code** code) {
  if (f->IsHeapObject() &&
      HEAP->Contains(HeapObject::cast(f)) &&
      HEAP->Contains(HeapObject::cast(f)->map()) &&
      HeapObject::cast(f)->map()->IsMap()) {
    if (f->IsJSFunction()) {
      JSFunction* fun = JSFunction::cast(f);

      PrintPrototype(fun, receiver);
      *code = fun->code();
    } else if (f->IsSymbol()) {


      PrintName(f);
      Add("/* unresolved */ ");
    } else {


      Add("%o", f);
      Add("/* warning: no JSFunction object or function name found */ ");
    }


  } else {
    if (!f->IsHeapObject()) {
      Add("/* warning: 'function' was not a heap object */ ");
      return;
    }
    if (!HEAP->Contains(HeapObject::cast(f))) {
      Add("/* warning: 'function' was not on the heap */ ");
      return;
    }
    if (!HEAP->Contains(HeapObject::cast(f)->map())) {
      Add("/* warning: function's map was not on the heap */ ");
      return;
    }
    if (!HeapObject::cast(f)->map()->IsMap()) {
      Add("/* warning: function's map was not a valid map */ ");
      return;
    }
    Add("/* warning: Invalid JSFunction object found */ ");
  }
}
