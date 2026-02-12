bool TensorSlice::Intersect(const TensorSlice& other,
                            TensorSlice* result) const {


  if (dims() != other.dims()) {
    return false;
  }


  if (result) {
    result->SetFullSlice(dims());
  }

  for (int d = 0; d < dims(); ++d) {
    if (IsFullAt(d)) {
      if (result) {
        result->set_start(d, other.start(d));
        result->set_length(d, other.length(d));
      }
    } else if (other.IsFullAt(d)) {
      if (result) {
        result->set_start(d, start(d));
        result->set_length(d, length(d));
      }
    } else {


      int64_t s = std::max(start(d), other.start(d));
      int64_t l = std::min(end(d), other.end(d)) - s;
      if (l > 0) {

        if (result) {
          result->set_start(d, s);
          result->set_length(d, l);
        }
      } else {


        if (result) {
          result->Clear();
        }
        return false;
      }
    }
  }

  return true;
}
