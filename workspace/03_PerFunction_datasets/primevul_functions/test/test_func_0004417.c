void Compute(OpKernelContext* context) override {
    core::RefCountPtr<QuantileStreamResource> streams_resource;

    OP_REQUIRES_OK(context, LookupResource(context, HandleFromInput(context, 0),
                                           &streams_resource));

    mutex_lock l(*streams_resource->mutex());

    OpInputList bucket_boundaries_list;
    OP_REQUIRES_OK(context, context->input_list(kBucketBoundariesName,
                                                &bucket_boundaries_list));

    auto do_quantile_deserialize = [&](const int64_t begin, const int64_t end) {

      for (int64_t stream_idx = begin; stream_idx < end; stream_idx++) {
        const Tensor& bucket_boundaries_t = bucket_boundaries_list[stream_idx];
        const auto& bucket_boundaries = bucket_boundaries_t.vec<float>();
        std::vector<float> result;
        result.reserve(bucket_boundaries.size());
        for (size_t i = 0; i < bucket_boundaries.size(); ++i) {
          result.push_back(bucket_boundaries(i));
        }
        streams_resource->set_boundaries(result, stream_idx);
      }
    };


    const int64_t kCostPerUnit = 500 * num_features_;
    const DeviceBase::CpuWorkerThreads& worker_threads =
        *context->device()->tensorflow_cpu_worker_threads();
    Shard(worker_threads.num_threads, worker_threads.workers, num_features_,
          kCostPerUnit, do_quantile_deserialize);
  }
