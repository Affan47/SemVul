void ExtractValue(DimensionHandle d, int64_t* result) {
    if (!InferenceContext::ValueKnown(d)) {
      *result = -counter;
      counter++;
    } else {
      int64_t val = InferenceContext::Value(d);
      if (val >= 0) {
        *result = val;
      } else {


        *result = -counter;
        counter++;
      }
    }
  }
