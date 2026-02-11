dont_cross_ocean(const struct tile *ptile,
                                           enum known_type known,
                                           const struct pf_parameter *param)
{
  if (!is_native_tile_to_class(param->uclass, ptile)) {
    return TB_DONT_LEAVE;
  }
  return TB_NORMAL;
}
