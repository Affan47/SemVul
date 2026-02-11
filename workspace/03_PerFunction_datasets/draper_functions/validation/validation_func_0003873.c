can_city_build_improvement_direct(const struct city *pcity,
				       struct impr_type *pimprove)
{
  if (!can_player_build_improvement_direct(city_owner(pcity), pimprove)) {
    return FALSE;
  }

  if (city_has_building(pcity, pimprove)) {
    return FALSE;
  }

  return are_reqs_active(city_owner(pcity), pcity, NULL,
			 pcity->tile, NULL, NULL, NULL,
			 &(pimprove->reqs), RPT_CERTAIN);
}
