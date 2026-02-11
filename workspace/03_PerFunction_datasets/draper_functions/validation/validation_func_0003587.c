eh_region_may_contain_throw (eh_region r)
{
  return r && bitmap_bit_p (eh_region_may_contain_throw_map, r->index);
}
