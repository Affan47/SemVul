void imap_expunge_mailbox(struct Mailbox *m)
{
  struct ImapAccountData *adata = imap_adata_get(m);
  struct ImapMboxData *mdata = imap_mdata_get(m);
  if (!adata || !mdata)
    return;

  struct Email *e = NULL;

#ifdef USE_HCACHE
  imap_hcache_open(adata, mdata);
#endif

  for (int i = 0; i < m->msg_count; i++)
  {
    e = m->emails[i];
    if (!e)
      break;

    if (e->index == INT_MAX)
    {
      mutt_debug(LL_DEBUG2, "Expunging message UID %u\n", imap_edata_get(e)->uid);

      e->deleted = true;

      imap_cache_del(m, e);
#ifdef USE_HCACHE
      imap_hcache_del(mdata, imap_edata_get(e)->uid);
#endif

      mutt_hash_int_delete(mdata->uid_hash, imap_edata_get(e)->uid, e);

      imap_edata_free((void **) &e->edata);
    }
    else
    {


      e->active = true;
    }
  }

#ifdef USE_HCACHE
  imap_hcache_close(mdata);
#endif

  mailbox_changed(m, NT_MAILBOX_UPDATE);
  mailbox_changed(m, NT_MAILBOX_RESORT);
}
