setup_resolution(stp_vars_t *v)
{
  escp2_privdata_t *pd = get_privdata(v);
  const res_t *res = stp_escp2_find_resolution(v);

  int vertical = adjusted_vertical_resolution(res);
  int horizontal = adjusted_horizontal_resolution(res);

  pd->res = res;
  pd->use_extended_commands =
    escp2_use_extended_commands(v, !(pd->res->command));
  pd->physical_xdpi = escp2_base_res(v);
  if (pd->physical_xdpi > pd->res->hres)
    pd->physical_xdpi = pd->res->hres;

  if (pd->use_extended_commands)
    {
      pd->unit_scale = MAX(escp2_max_hres(v), escp2_max_vres(v));
      pd->horizontal_units = horizontal;
      pd->micro_units = horizontal;
    }
  else
    {
      pd->unit_scale = 3600;
      if (pd->res->hres <= 720)
	pd->micro_units = vertical;
      else
	pd->micro_units = horizontal;
      pd->horizontal_units = vertical;
    }

  if (stp_escp2_has_cap(v, MODEL_COMMAND, MODEL_COMMAND_1999) &&
      stp_escp2_has_cap(v, MODEL_VARIABLE_DOT, MODEL_VARIABLE_NO))
    pd->micro_units = 1440;
  pd->vertical_units = vertical;
  pd->page_management_units = vertical;
}
