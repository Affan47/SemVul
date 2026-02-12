dirserv_count_measured_bws(const smartlist_t *routers)
{

  routers_with_measured_bw = 0;


  SMARTLIST_FOREACH_BEGIN(routers, const routerinfo_t *, ri) {

    if (dirserv_has_measured_bw(ri->cache_info.identity_digest)) {
      ++routers_with_measured_bw;
    }
  } SMARTLIST_FOREACH_END(ri);
}
