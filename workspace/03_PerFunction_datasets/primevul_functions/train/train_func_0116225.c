explicit ExceptionScope(Isolate* isolate) :


      isolate_(isolate),
      pending_exception_(isolate_->pending_exception()->ToObjectUnchecked()),
      catcher_(isolate_->catcher())
    { }
