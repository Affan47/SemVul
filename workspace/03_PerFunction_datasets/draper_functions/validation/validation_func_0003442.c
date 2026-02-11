gt_shu_unit_file_info_read(const GtStr *unitfile,
                               GtShuUnitFileInfo *unit_info,
                               GT_UNUSED GtLogger *logger,
                               GtError *err)
{
  int had_err = 0;

  lua_State *L = luaL_newstate();


  had_err = shu_unitfile_load(L, gt_str_get(unitfile), err);
  if (!had_err)
    had_err = traverse_units(L, unit_info, err);

  lua_close(L);
  return had_err;
}
