clutter_actor_get_anchor_point_gravity (ClutterActor *self)
{
  const ClutterTransformInfo *info;

  g_return_val_if_fail (CLUTTER_IS_ACTOR (self), CLUTTER_GRAVITY_NONE);

  info = _clutter_actor_get_transform_info_or_defaults (self);

  return clutter_anchor_coord_get_gravity (&info->anchor);
}
