void Compute(OpKernelContext* ctx) override {
    StagingMap<Ordered>* map = nullptr;
    OP_REQUIRES_OK(ctx, GetStagingMap(ctx, def(), &map));
    core::ScopedUnref scope(map);


    typename StagingMap<Ordered>::KeyType key;
    typename StagingMap<Ordered>::Tuple tuple;

    const Tensor* indices_tensor;

    OP_REQUIRES_OK(ctx, ctx->input("indices", &indices_tensor));
    OP_REQUIRES_OK(ctx, map->popitem(&key, indices_tensor, &tuple));


    ctx->set_output(0, key);


    OP_REQUIRES(
        ctx, tuple.size() == indices_tensor->NumElements(),
        errors::InvalidArgument("output/indices size mismatch: ", tuple.size(),
                                " vs. ", indices_tensor->NumElements()));

    for (std::size_t i = 0; i < tuple.size(); ++i) {
      ctx->set_output(i + 1, tuple[i]);
    }
  }
