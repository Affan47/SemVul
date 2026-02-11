unit_color_type(const struct unit_type *punittype)
{
  struct unit_class *pclass = utype_class(punittype);

  if (pclass->hp_loss_pct > 0) {
    return UNIT_BG_HP_LOSS;
  }

  if (pclass->move_type == UMT_LAND) {
    return UNIT_BG_LAND;
  }
  if (pclass->move_type == UMT_SEA) {
    return UNIT_BG_SEA;
  }

  fc_assert(pclass->move_type == UMT_BOTH);

  if (uclass_has_flag(pclass, UCF_TERRAIN_SPEED)) {

    return UNIT_BG_AMPHIBIOUS;
  }

  return UNIT_BG_FLYING;
}
