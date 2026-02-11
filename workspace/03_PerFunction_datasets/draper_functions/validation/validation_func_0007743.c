add_dim(NcToken name, long size)
{
    if (!is_valid() || !define_mode())
      return 0;
    int n = num_dims();
    NcDim* dimp = new NcDim(this, name, size);
    dimensions[n] = dimp;
    return dimp;
}
