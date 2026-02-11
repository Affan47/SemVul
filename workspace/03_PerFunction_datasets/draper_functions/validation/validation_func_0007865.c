range (edict_t * self, edict_t * other)
{
  vec3_t v;
  float len;

  VectorSubtract (self->s.origin, other->s.origin, v);
  len = VectorLength (v);
  if (len < MELEE_DISTANCE)
    return RANGE_MELEE;
  if (len < 500)
    return RANGE_NEAR;
  if (len < 1000)
    return RANGE_MID;
  return RANGE_FAR;
}
