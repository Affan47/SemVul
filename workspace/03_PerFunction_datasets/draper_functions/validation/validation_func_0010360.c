StopThread() {
    if (the_thread_ == NULL) return;

    the_thread_->keep_running_ = false;
    wait_for_ever_semaphore_->Signal();


    the_thread_->Join();

    if (data_ready_semaphore_ != NULL) {
      delete data_ready_semaphore_;
      data_ready_semaphore_ = NULL;
    }

    delete wait_for_ever_semaphore_;
    wait_for_ever_semaphore_ = NULL;


    delete the_thread_;
    the_thread_ = NULL;
  }
