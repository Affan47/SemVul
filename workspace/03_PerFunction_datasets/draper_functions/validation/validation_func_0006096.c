get_drawable_unit(const struct tileset *t,
			       struct tile *ptile,
			       const struct city *citymode)
{
  struct unit *punit = find_visible_unit(ptile);

  if (!punit)
    return NULL;

  if (citymode && unit_owner(punit) == city_owner(citymode))
    return NULL;

  if (!unit_is_in_focus(punit)
      || t->sprites.unit.select[0] || focus_unit_state == 0)
    return punit;
  else
    return NULL;
}
