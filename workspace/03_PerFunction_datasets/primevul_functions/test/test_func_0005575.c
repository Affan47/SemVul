void Get(Tuple* tuple) {
    std::unique_lock<std::mutex> lock(mu_);


    non_empty_cond_var_.wait(lock, [this]() { return !buf_.empty(); });


    *tuple = std::move(buf_.front());
    buf_.pop_front();


    current_bytes_ -= GetTupleBytes(*tuple);

    notify_inserters_if_bounded(&lock);
  }
