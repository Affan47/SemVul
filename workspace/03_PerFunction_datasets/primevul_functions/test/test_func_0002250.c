Status put(KeyType* key, const Tensor* indices, OptionalTuple* tuple) {
    tensorflow::mutex_lock lock(mu_);


    TF_RETURN_IF_ERROR(check_index_ordering(*indices));


    if (indices->NumElements() != dtypes_.size()) {
      return put_incomplete(*key, *indices, tuple, &lock);
    }

    std::size_t tuple_bytes = get_tuple_bytes(*tuple);

    TF_RETURN_IF_ERROR(check_memory_limit(tuple_bytes));


    while (would_exceed_memory_limit(tuple_bytes) || is_capacity_full()) {
      full_.wait(lock);
    }


    TF_RETURN_IF_ERROR(put_complete(*key, tuple));


    current_bytes_ += tuple_bytes;

    return Status::OK();
  }
