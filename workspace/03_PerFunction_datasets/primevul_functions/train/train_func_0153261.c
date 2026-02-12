lookup (getkey_ctx_t ctx, kbnode_t *ret_keyblock, int want_secret)
{
  int rc;
  int no_suitable_key = 0;

  rc = 0;
  while (!(rc = keydb_search (ctx->kr_handle, ctx->items, ctx->nitems)))
    {


      if (ctx->nitems && ctx->items->mode == KEYDB_SEARCH_MODE_FIRST)
	ctx->items->mode = KEYDB_SEARCH_MODE_NEXT;

      rc = keydb_get_keyblock (ctx->kr_handle, &ctx->keyblock);
      if (rc)
	{
	  log_error ("keydb_get_keyblock failed: %s\n", g10_errstr (rc));
	  rc = 0;
	  goto skip;
	}

      if (want_secret && agent_probe_any_secret_key (NULL, ctx->keyblock))
        goto skip;


      merge_selfsigs (ctx->keyblock);
      if (finish_lookup (ctx))
	{
	  no_suitable_key = 0;
	  goto found;
	}
      else
	no_suitable_key = 1;

    skip:

      release_kbnode (ctx->keyblock);
      ctx->keyblock = NULL;
    }

found:
  if (rc && gpg_err_code (rc) != GPG_ERR_NOT_FOUND)
    log_error ("keydb_search failed: %s\n", g10_errstr (rc));

  if (!rc)
    {
      *ret_keyblock = ctx->keyblock;
      ctx->keyblock = NULL;
    }
  else if (gpg_err_code (rc) == GPG_ERR_NOT_FOUND && no_suitable_key)
    rc = want_secret? G10ERR_UNU_SECKEY : G10ERR_UNU_PUBKEY;
  else if (gpg_err_code (rc) == GPG_ERR_NOT_FOUND)
    rc = want_secret? G10ERR_NO_SECKEY : G10ERR_NO_PUBKEY;

  release_kbnode (ctx->keyblock);
  ctx->keyblock = NULL;

  ctx->last_rc = rc;
  return rc;
}
