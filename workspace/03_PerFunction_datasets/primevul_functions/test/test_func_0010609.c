ciEnv::~ciEnv() {
  CompilerThread* current_thread = CompilerThread::current();
  _factory->remove_symbols();


  GUARDED_VM_ENTRY(current_thread->set_env(NULL);)
}
