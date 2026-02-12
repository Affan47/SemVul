get_pubkey_byname (ctrl_t ctrl, GETKEY_CTX * retctx, PKT_public_key * pk,
		   const char *name, KBNODE * ret_keyblock,
		   KEYDB_HANDLE * ret_kdbhd, int include_unusable, int no_akl)
{
  int rc;
  strlist_t namelist = NULL;
  struct akl *akl;
  int is_mbox;
  int nodefault = 0;
  int anylocalfirst = 0;

  if (retctx)
    *retctx = NULL;

  is_mbox = is_valid_mailbox (name);


  if (!no_akl)
    {
      for (akl = opt.auto_key_locate; akl; akl = akl->next)
	if (akl->type == AKL_NODEFAULT || akl->type == AKL_LOCAL)
	  {
	    nodefault = 1;
	    break;
	  }
      for (akl = opt.auto_key_locate; akl; akl = akl->next)
	if (akl->type != AKL_NODEFAULT)
	  {
	    if (akl->type == AKL_LOCAL)
	      anylocalfirst = 1;
	    break;
	  }
    }

  if (!nodefault)
    anylocalfirst = 1;

  if (nodefault && is_mbox)
    {

      rc = G10ERR_NO_PUBKEY;
    }
  else
    {
      add_to_strlist (&namelist, name);
      rc = key_byname (retctx, namelist, pk, 0,
		       include_unusable, ret_keyblock, ret_kdbhd);
    }


  if (gpg_err_code (rc) == G10ERR_NO_PUBKEY && !no_akl && is_mbox)
    {
      for (akl = opt.auto_key_locate; akl; akl = akl->next)
	{
	  unsigned char *fpr = NULL;
	  size_t fpr_len;
	  int did_key_byname = 0;
	  int no_fingerprint = 0;
	  const char *mechanism = "?";

	  switch (akl->type)
	    {
	    case AKL_NODEFAULT:

	      mechanism = "None";
	      rc = G10ERR_NO_PUBKEY;
	      break;

	    case AKL_LOCAL:
	      mechanism = "Local";
	      did_key_byname = 1;
	      if (retctx)
		{
		  get_pubkey_end (*retctx);
		  *retctx = NULL;
		}
	      add_to_strlist (&namelist, name);
	      rc = key_byname (anylocalfirst ? retctx : NULL,
			       namelist, pk, 0,
			       include_unusable, ret_keyblock, ret_kdbhd);
	      break;

	    case AKL_CERT:
	      mechanism = "DNS CERT";
	      glo_ctrl.in_auto_key_retrieve++;
	      rc = keyserver_import_cert (ctrl, name, &fpr, &fpr_len);
	      glo_ctrl.in_auto_key_retrieve--;
	      break;

	    case AKL_PKA:
	      mechanism = "PKA";
	      glo_ctrl.in_auto_key_retrieve++;
	      rc = keyserver_import_pka (ctrl, name, &fpr, &fpr_len);
	      glo_ctrl.in_auto_key_retrieve--;
	      break;

	    case AKL_LDAP:
	      mechanism = "LDAP";
	      glo_ctrl.in_auto_key_retrieve++;
	      rc = keyserver_import_ldap (ctrl, name, &fpr, &fpr_len);
	      glo_ctrl.in_auto_key_retrieve--;
	      break;

	    case AKL_KEYSERVER:


	      if (opt.keyserver)
		{
		  mechanism = opt.keyserver->uri;
		  glo_ctrl.in_auto_key_retrieve++;
		  rc = keyserver_import_name (ctrl, name, &fpr, &fpr_len,
                                              opt.keyserver);
		  glo_ctrl.in_auto_key_retrieve--;
		}
	      else
		{
		  mechanism = "Unconfigured keyserver";
		  rc = G10ERR_NO_PUBKEY;
		}
	      break;

	    case AKL_SPEC:
	      {
		struct keyserver_spec *keyserver;

		mechanism = akl->spec->uri;
		keyserver = keyserver_match (akl->spec);
		glo_ctrl.in_auto_key_retrieve++;
		rc = keyserver_import_name (ctrl,
                                            name, &fpr, &fpr_len, keyserver);
		glo_ctrl.in_auto_key_retrieve--;
	      }
	      break;
	    }


	  if (!rc && fpr)
	    {
	      char fpr_string[MAX_FINGERPRINT_LEN * 2 + 1];

	      assert (fpr_len <= MAX_FINGERPRINT_LEN);

	      free_strlist (namelist);
	      namelist = NULL;

	      bin2hex (fpr, fpr_len, fpr_string);

	      if (opt.verbose)
		log_info ("auto-key-locate found fingerprint %s\n",
			  fpr_string);

	      add_to_strlist (&namelist, fpr_string);
	    }
	  else if (!rc && !fpr && !did_key_byname)
	    {
	      no_fingerprint = 1;
	      rc = G10ERR_NO_PUBKEY;
	    }
	  xfree (fpr);
	  fpr = NULL;

	  if (!rc && !did_key_byname)
	    {
	      if (retctx)
		{
		  get_pubkey_end (*retctx);
		  *retctx = NULL;
		}
	      rc = key_byname (anylocalfirst ? retctx : NULL,
			       namelist, pk, 0,
			       include_unusable, ret_keyblock, ret_kdbhd);
	    }
	  if (!rc)
	    {

	      log_info (_("automatically retrieved '%s' via %s\n"),
			name, mechanism);
	      break;
	    }
	  if (rc != G10ERR_NO_PUBKEY || opt.verbose || no_fingerprint)
	    log_info (_("error retrieving '%s' via %s: %s\n"),
		      name, mechanism,
		      no_fingerprint ? _("No fingerprint") : g10_errstr (rc));
	}
    }


  if (rc && retctx)
    {
      get_pubkey_end (*retctx);
      *retctx = NULL;
    }

  if (retctx && *retctx)
    {
      assert (!(*retctx)->extra_list);
      (*retctx)->extra_list = namelist;
    }
  else
    free_strlist (namelist);
  return rc;
}
