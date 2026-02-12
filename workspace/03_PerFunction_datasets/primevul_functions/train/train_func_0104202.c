int imap_sync_mailbox (CONTEXT* ctx, int expunge, int* index_hint)
{
  IMAP_DATA* idata;
  CONTEXT* appendctx = NULL;
  HEADER* h;
  HEADER** hdrs = NULL;
  int oldsort;
  int n;
  int rc, quickdel_rc = 0;

  idata = (IMAP_DATA*) ctx->data;

  if (idata->state < IMAP_SELECTED)
  {
    dprint (2, (debugfile, "imap_sync_mailbox: no mailbox selected\n"));
    return -1;
  }


  imap_allow_reopen (ctx);

  if ((rc = imap_check_mailbox (ctx, index_hint, 0)) != 0)
    goto out;


  if (expunge && mutt_bit_isset (ctx->rights, MUTT_ACL_DELETE))
  {
    if ((quickdel_rc = imap_exec_msgset (idata,
                                         "UID STORE", "+FLAGS.SILENT (\\Deleted)",
                                         MUTT_DELETED, 1, 0)) < 0)
    {
      rc = quickdel_rc;
      mutt_error (_("Expunge failed"));
      mutt_sleep (1);
      goto out;
    }

    if (quickdel_rc > 0)
    {


      for (n = 0; n < ctx->msgcount; n++)
        if (ctx->hdrs[n]->deleted && ctx->hdrs[n]->changed)
          ctx->hdrs[n]->active = 0;
      if (!ctx->quiet)
        mutt_message (_("Marking %d messages deleted..."), quickdel_rc);
    }
  }

#if USE_HCACHE
  idata->hcache = imap_hcache_open (idata, NULL);
#endif


  for (n = 0; n < ctx->msgcount; n++)
  {
    h = ctx->hdrs[n];

    if (h->deleted)
    {
      imap_cache_del (idata, h);
#if USE_HCACHE
      imap_hcache_del (idata, HEADER_DATA(h)->uid);
#endif
    }

    if (h->active && h->changed)
    {
#if USE_HCACHE
      imap_hcache_put (idata, h);
#endif


      if ((h->env && h->env->changed) || h->attach_del)
      {


#if USE_HCACHE
        imap_hcache_close (idata);
#endif
        if (!ctx->quiet)
          mutt_message (_("Saving changed messages... [%d/%d]"), n+1,
                        ctx->msgcount);
	if (!appendctx)
	  appendctx = mx_open_mailbox (ctx->path, MUTT_APPEND | MUTT_QUIET, NULL);
	if (!appendctx)
	  dprint (1, (debugfile, "imap_sync_mailbox: Error opening mailbox in append mode\n"));
	else
	  _mutt_save_message (h, appendctx, 1, 0, 0);

        if (h->env)
          h->env->changed = 0;
#if USE_HCACHE
        idata->hcache = imap_hcache_open (idata, NULL);
#endif
      }
    }
  }

#if USE_HCACHE
  imap_hcache_close (idata);
#endif


  imap_disallow_reopen (ctx);
  oldsort = Sort;
  if (Sort != SORT_ORDER)
  {
    hdrs = ctx->hdrs;
    ctx->hdrs = safe_malloc (ctx->msgcount * sizeof (HEADER*));
    memcpy (ctx->hdrs, hdrs, ctx->msgcount * sizeof (HEADER*));

    Sort = SORT_ORDER;
    qsort (ctx->hdrs, ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  rc = sync_helper (idata, MUTT_ACL_DELETE, MUTT_DELETED, "\\Deleted");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_WRITE, MUTT_FLAG, "\\Flagged");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_WRITE, MUTT_OLD, "Old");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_SEEN, MUTT_READ, "\\Seen");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_WRITE, MUTT_REPLIED, "\\Answered");

  if ((oldsort != Sort) || hdrs)
  {
    Sort = oldsort;
    FREE (&ctx->hdrs);
    ctx->hdrs = hdrs;
  }
  imap_allow_reopen (ctx);


  if (((rc > 0) || (quickdel_rc > 0)) && mutt_buffer_len (idata->cmdbuf))
    if (imap_exec (idata, NULL, 0) != IMAP_CMD_OK)
      rc = -1;

  if (rc < 0)
  {
    if (ctx->closing)
    {
      if (mutt_yesorno (_("Error saving flags. Close anyway?"), 0) == MUTT_YES)
      {
        rc = 0;
        idata->state = IMAP_AUTHENTICATED;
        goto out;
      }
    }
    else
      mutt_error _("Error saving flags");
    rc = -1;
    goto out;
  }


  for (n = 0; n < ctx->msgcount; n++)
  {
    HEADER_DATA(ctx->hdrs[n])->deleted = ctx->hdrs[n]->deleted;
    HEADER_DATA(ctx->hdrs[n])->flagged = ctx->hdrs[n]->flagged;
    HEADER_DATA(ctx->hdrs[n])->old = ctx->hdrs[n]->old;
    HEADER_DATA(ctx->hdrs[n])->read = ctx->hdrs[n]->read;
    HEADER_DATA(ctx->hdrs[n])->replied = ctx->hdrs[n]->replied;
    ctx->hdrs[n]->changed = 0;
  }
  ctx->changed = 0;


  if (expunge && !(ctx->closing) &&
      mutt_bit_isset(ctx->rights, MUTT_ACL_DELETE))
  {
    if (!ctx->quiet)
      mutt_message _("Expunging messages from server...");

    idata->reopen |= IMAP_EXPUNGE_EXPECTED;
    if (imap_exec (idata, "EXPUNGE", 0) != 0)
    {
      idata->reopen &= ~IMAP_EXPUNGE_EXPECTED;
      imap_error (_("imap_sync_mailbox: EXPUNGE failed"), idata->buf);
      rc = -1;
      goto out;
    }
    idata->reopen &= ~IMAP_EXPUNGE_EXPECTED;
  }

  if (expunge && ctx->closing)
  {
    imap_exec (idata, "CLOSE", IMAP_CMD_QUEUE);
    idata->state = IMAP_AUTHENTICATED;
  }

  if (option (OPTMESSAGECACHECLEAN))
    imap_cache_clean (idata);

  rc = 0;

out:
  imap_disallow_reopen (ctx);
  if (appendctx)
  {
    mx_fastclose_mailbox (appendctx);
    FREE (&appendctx);
  }
  return rc;
}
