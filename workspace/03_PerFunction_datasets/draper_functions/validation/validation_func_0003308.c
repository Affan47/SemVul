gimple_ior_addresses_taken_1 (gimple, tree addr, tree, void *data)
{
  bitmap addresses_taken = (bitmap)data;
  addr = get_base_address (addr);
  if (addr
      && DECL_P (addr))
    {
      bitmap_set_bit (addresses_taken, DECL_UID (addr));
      return true;
    }
  return false;
}
