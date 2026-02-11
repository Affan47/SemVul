match_source_mode_dim (source_mode sm)
{
  DBG (3, "match_source_mode_dim: %d\n", sm);

  switch (sm) {
  case AV_NORMAL:
    return AV_NORMAL_DIM;
  case AV_TRANSPARENT:
    return AV_TRANSPARENT_DIM;
  case AV_ADF:
  case AV_ADF_REAR:
  case AV_ADF_DUPLEX:
    return AV_ADF_DIM;
  default:
    DBG (3, "match_source_mode_dim: source mode invalid\n");
    return AV_NORMAL_DIM;
  }
}
