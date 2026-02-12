void imap_expunge_mailbox (IMAP_DATA* idata)
{
  HEADER* h;
  int i, cacheno;
  short old_sort;

#ifdef USE_HCACHE
  idata->hcache = imap_hcache_open (idata, NULL);
#endif

  old_sort = Sort;
  Sort = SORT_ORDER;
  mutt_sort_headers (idata->ctx, 0);

  for (i = 0; i < idata->ctx->msgcount; i++)
  {
    h = idata->ctx->hdrs[i];

    if (h->index == INT_MAX)
    {
      dprint (2, (debugfile, "Expunging message UID %u.\n", HEADER_DATA (h)->uid));

      h->active = 0;
      idata->ctx->size -= h->content->length;

      imap_cache_del (idata, h);
#if USE_HCACHE
      imap_hcache_del (idata, HEADER_DATA(h)->uid);
#endif


      cacheno = HEADER_DATA(h)->uid % IMAP_CACHE_LEN;
      if (idata->cache[cacheno].uid == HEADER_DATA(h)->uid &&
	  idata->cache[cacheno].path)
      {
	unlink (idata->cache[cacheno].path);
	FREE (&idata->cache[cacheno].path);
      }

      int_hash_delete (idata->uid_hash, HEADER_DATA(h)->uid, h, NULL);

      imap_free_header_data ((IMAP_HEADER_DATA**)&h->data);
    }
    else
    {
      h->index = i;


      h->active = 1;
    }
  }

#if USE_HCACHE
  imap_hcache_close (idata);
#endif


  mx_update_tables (idata->ctx, 0);
  Sort = old_sort;
  mutt_sort_headers (idata->ctx, 1);
}
