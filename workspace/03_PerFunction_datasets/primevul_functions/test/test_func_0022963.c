int ha_maria::check_for_upgrade(HA_CHECK_OPT *check)
{
  if (table->s->mysql_version && table->s->mysql_version <= 100509 &&
      (file->s->base.extra_options & MA_EXTRA_OPTIONS_ENCRYPTED))
  {


    return HA_ADMIN_NEEDS_ALTER;
  }
  return HA_ADMIN_OK;
}
