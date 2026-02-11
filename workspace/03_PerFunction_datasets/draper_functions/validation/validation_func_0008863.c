StartPreemption(int every_n_ms) {
  Isolate* isolate = Isolate::Current();
  ASSERT(Locker::IsLocked(reinterpret_cast<v8::Isolate*>(isolate)));
  if (isolate->context_switcher() == NULL) {

    isolate->set_context_switcher(new ContextSwitcher(isolate, every_n_ms));
    isolate->context_switcher()->Start();
  } else {


    isolate->context_switcher()->sleep_ms_ = every_n_ms;
  }
}
