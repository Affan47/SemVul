~SubgraphGuard() {

    if (status_ == kTfLiteOk) {
      *is_subgraph_in_use_ = false;
    }
  }
