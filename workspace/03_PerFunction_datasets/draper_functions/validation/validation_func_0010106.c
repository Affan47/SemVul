matches (const MatchType &type) const {
  if (type != *this)
    return false;
  MTArray &matched_type = (MTArray&)type;
  return base ()->matches (*matched_type.base ()) &&
    (_any_size || _dim == matched_type._dim);
}
