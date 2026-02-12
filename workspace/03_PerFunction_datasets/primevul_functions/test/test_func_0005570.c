Status Put(Tuple* tuple) {
    std::unique_lock<std::mutex> lock(mu_);

    std::size_t tuple_bytes = GetTupleBytes(*tuple);


    if (memory_limit_ > 0 && tuple_bytes > memory_limit_) {
      return Status(
          errors::ResourceExhausted("Attempted to insert "
                                    "tensors with combined size of '",
                                    tuple_bytes,
                                    "' bytes into "
                                    "Staging Area with a memory limit of '",
                                    memory_limit_, "'."));
    }


    if (IsBounded()) {
      full_cond_var_.wait(lock, [tuple_bytes, this]() {

        bool memory_limit_valid =
            memory_limit_ > 0 ? !WouldExceedMemoryLimit(tuple_bytes) : true;

        bool capacity_valid = capacity_ > 0 ? !IsCapacityFull() : true;


        return capacity_valid && memory_limit_valid;
      });
    }


    current_bytes_ += tuple_bytes;


    buf_.push_back(std::move(*tuple));

    lock.unlock();


    non_empty_cond_var_.notify_all();

    return Status::OK();
  }
