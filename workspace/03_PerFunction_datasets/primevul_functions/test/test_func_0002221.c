Status pop(const KeyType* key, const Tensor* indices, Tuple* tuple) {
    tensorflow::mutex_lock lock(mu_);


    TF_RETURN_IF_ERROR(check_index_ordering(*indices));

    typename MapType::iterator it;


    while ((it = map_.find(*key)) == map_.end()) {
      not_empty_.wait(lock);
    }

    TF_RETURN_IF_ERROR(
        copy_or_move_tensors(&it->second, *key, *indices, tuple));


    if (!std::any_of(
            it->second.begin(), it->second.end(),
            [](const OptionalTensor& tensor) { return tensor.has_value(); })) {
      map_.erase(it);
    }


    current_bytes_ -= get_tuple_bytes(*tuple);

    notify_inserters_if_bounded();

    return Status::OK();
  }
