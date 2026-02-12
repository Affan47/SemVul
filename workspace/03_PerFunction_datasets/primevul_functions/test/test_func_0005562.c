Status Peek(std::size_t index, Tuple* tuple) {
    std::unique_lock<std::mutex> lock(mu_);


    non_empty_cond_var_.wait(
        lock, [index, this]() { return index < this->buf_.size(); });


    for (const auto& tensor : buf_[index]) {
      tuple->push_back(tensor);
    }

    return Status::OK();
  }
