fribidi_set_mirroring (

  fribidi_boolean state
)
{
  return FRIBIDI_ADJUST_AND_TEST_BITS (flags, FRIBIDI_FLAG_SHAPE_MIRRORING, state);
}
