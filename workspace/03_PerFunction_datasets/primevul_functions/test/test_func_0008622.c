Tensor UnalignedSlice(const Tensor& t, int pos) const {
    Tensor res;

    CHECK(res.CopyFrom(t.Slice(pos, pos + 1), {t.dim_size(1), t.dim_size(2)}));
    return res;
  }
