routers_make_ed_keys_unique(smartlist_t *routers)
{
  routerinfo_t *ri2;
  digest256map_t *by_ed_key = digest256map_new();

  SMARTLIST_FOREACH_BEGIN(routers, routerinfo_t *, ri) {
    ri->omit_from_vote = 0;
    if (ri->cache_info.signing_key_cert == NULL)
      continue;
    const uint8_t *pk = ri->cache_info.signing_key_cert->signing_key.pubkey;
    if ((ri2 = digest256map_get(by_ed_key, pk))) {


      const time_t ri_pub = ri->cache_info.published_on;
      const time_t ri2_pub = ri2->cache_info.published_on;
      if (ri2_pub < ri_pub ||
          (ri2_pub == ri_pub &&
           fast_memcmp(ri->cache_info.signed_descriptor_digest,
                     ri2->cache_info.signed_descriptor_digest,DIGEST_LEN)<0)) {
        digest256map_set(by_ed_key, pk, ri);
        ri2->omit_from_vote = 1;
      } else {
        ri->omit_from_vote = 1;
      }
    } else {

      digest256map_set(by_ed_key, pk, ri);
    }
  } SMARTLIST_FOREACH_END(ri);

  digest256map_free(by_ed_key, NULL);


  SMARTLIST_FOREACH_BEGIN(routers, const routerinfo_t *, ri) {
    if (ri->omit_from_vote) {
      SMARTLIST_DEL_CURRENT(routers, ri);
    }
  } SMARTLIST_FOREACH_END(ri);
}
