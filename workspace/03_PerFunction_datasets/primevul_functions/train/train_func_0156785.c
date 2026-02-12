dirserv_should_launch_reachability_test(const routerinfo_t *ri,
                                        const routerinfo_t *ri_old)
{
  if (!authdir_mode_handles_descs(get_options(), ri->purpose))
    return 0;
  if (!ri_old) {


    return 1;
  }
  if (ri_old->is_hibernating && !ri->is_hibernating) {

    return 1;
  }
  if (! routers_have_same_or_addrs(ri, ri_old)) {

    return 1;
  }
  return 0;
}
