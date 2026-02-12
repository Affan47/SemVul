void notify_inserters_if_bounded(std::unique_lock<std::mutex>* lock) {
    if (IsBounded()) {
      lock->unlock();


      full_cond_var_.notify_all();
    }
  }
