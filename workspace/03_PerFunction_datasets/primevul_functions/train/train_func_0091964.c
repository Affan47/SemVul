Status CalculateMultiplesFromChain(const std::vector<const NodeDef*>& chain,
                                     Tensor* multiples) {


    std::vector<int32> dims(multiples->NumElements());
    std::iota(dims.begin(), dims.end(), 0);

    for (int i = 0; i < multiples->NumElements(); ++i) {
      multiples->flat<int32>()(i) = 1;
    }

    for (auto it = chain.rbegin(); it != chain.rend(); ++it) {
      AttrSlice attrs(**it);
      int64 axis, n;
      TF_RETURN_IF_ERROR(GetNodeAttr(attrs, "axis", &axis));
      TF_RETURN_IF_ERROR(GetNodeAttr(attrs, "N", &n));

      if (axis >= dims.size()) {


        return Status(error::OUT_OF_RANGE, "axis value out of range of dims");
      }

      int64 m = multiples->flat<int32>()(dims[axis]) * n;
      if (TF_PREDICT_FALSE(m > INT_MAX)) {
        return Status(error::OUT_OF_RANGE, "int32 overflow");
      }
      multiples->flat<int32>()(dims[axis]) = static_cast<int32>(m);


      dims.insert(dims.begin() + axis, dims[axis]);
    }

    return Status::OK();
  }
