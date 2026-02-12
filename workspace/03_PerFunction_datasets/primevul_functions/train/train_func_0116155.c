void SetCurrentVMState(StateTag state) {
    if (RuntimeProfiler::IsEnabled()) {

      ASSERT(thread_local_top_.isolate_ == this);
      StateTag current_state = thread_local_top_.current_vm_state_;
      if (current_state != JS && state == JS) {

        RuntimeProfiler::IsolateEnteredJS(this);
      } else if (current_state == JS && state != JS) {

        ASSERT(RuntimeProfiler::IsSomeIsolateInJS());
        RuntimeProfiler::IsolateExitedJS(this);
      } else {


        ASSERT((current_state == JS) == (state == JS));
      }
    }
    thread_local_top_.current_vm_state_ = state;
  }
