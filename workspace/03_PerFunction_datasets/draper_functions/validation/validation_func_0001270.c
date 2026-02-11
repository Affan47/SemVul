matches( const Key& xmap_cachekey ) const
{
  return
    key.spgr_descr().hash()  == xmap_cachekey.spgr_descr().hash() &&
    key.grid_sampling().nu() == xmap_cachekey.grid_sampling().nu() &&
    key.grid_sampling().nv() == xmap_cachekey.grid_sampling().nv() &&
    key.grid_sampling().nw() == xmap_cachekey.grid_sampling().nw();
}
