merge_selfsigs_main (KBNODE keyblock, int *r_revoked,
		     struct revoke_info *rinfo)
{
  PKT_public_key *pk = NULL;
  KBNODE k;
  u32 kid[2];
  u32 sigdate, uiddate, uiddate2;
  KBNODE signode, uidnode, uidnode2;
  u32 curtime = make_timestamp ();
  unsigned int key_usage = 0;
  u32 keytimestamp = 0;
  u32 key_expire = 0;
  int key_expire_seen = 0;
  byte sigversion = 0;

  *r_revoked = 0;
  memset (rinfo, 0, sizeof (*rinfo));

  if (keyblock->pkt->pkttype != PKT_PUBLIC_KEY)
    BUG ();
  pk = keyblock->pkt->pkt.public_key;
  keytimestamp = pk->timestamp;

  keyid_from_pk (pk, kid);
  pk->main_keyid[0] = kid[0];
  pk->main_keyid[1] = kid[1];

  if (pk->version < 4)
    {


      key_expire = pk->max_expiredate;
      key_expire_seen = 1;
    }


  xfree (pk->revkey);
  pk->revkey = NULL;
  pk->numrevkeys = 0;

  signode = NULL;
  sigdate = 0;
  for (k = keyblock; k && k->pkt->pkttype != PKT_USER_ID; k = k->next)
    {
      if (k->pkt->pkttype == PKT_SIGNATURE)
	{
	  PKT_signature *sig = k->pkt->pkt.signature;
	  if (sig->keyid[0] == kid[0] && sig->keyid[1] == kid[1])
	    {
	      if (check_key_signature (keyblock, k, NULL))
		;
	      else if (IS_KEY_REV (sig))
		{


		  *r_revoked = 1;
		  sig_to_revoke_info (sig, rinfo);
		}
	      else if (IS_KEY_SIG (sig))
		{


		  if (sig->revkey)
		    {
		      int i;

		      pk->revkey =
			xrealloc (pk->revkey, sizeof (struct revocation_key) *
				  (pk->numrevkeys + sig->numrevkeys));

		      for (i = 0; i < sig->numrevkeys; i++)
			memcpy (&pk->revkey[pk->numrevkeys++],
				sig->revkey[i],
				sizeof (struct revocation_key));
		    }

		  if (sig->timestamp >= sigdate)
		    {
		      if (sig->flags.expired)
			;
		      else
			{
			  sigdate = sig->timestamp;
			  signode = k;
			  if (sig->version > sigversion)
			    sigversion = sig->version;

			}
		    }
		}
	    }
	}
    }


  if (pk->revkey)
    {
      int i, j, x, changed = 0;

      for (i = 0; i < pk->numrevkeys; i++)
	{
	  for (j = i + 1; j < pk->numrevkeys; j++)
	    {
	      if (memcmp (&pk->revkey[i], &pk->revkey[j],
			  sizeof (struct revocation_key)) == 0)
		{


		  for (x = j; x < pk->numrevkeys - 1; x++)
		    pk->revkey[x] = pk->revkey[x + 1];

		  pk->numrevkeys--;
		  j--;
		  changed = 1;
		}
	    }
	}

      if (changed)
	pk->revkey = xrealloc (pk->revkey,
			       pk->numrevkeys *
			       sizeof (struct revocation_key));
    }

  if (signode)
    {


      PKT_signature *sig = signode->pkt->pkt.signature;
      const byte *p;

      key_usage = parse_key_usage (sig);

      p = parse_sig_subpkt (sig->hashed, SIGSUBPKT_KEY_EXPIRE, NULL);
      if (p && buffer_to_u32 (p))
	{
	  key_expire = keytimestamp + buffer_to_u32 (p);
	  key_expire_seen = 1;
	}


      pk->flags.valid = 1;
    }


  if (!*r_revoked && pk->revkey)
    for (k = keyblock; k && k->pkt->pkttype != PKT_USER_ID; k = k->next)
      {
	if (k->pkt->pkttype == PKT_SIGNATURE)
	  {
	    PKT_signature *sig = k->pkt->pkt.signature;

	    if (IS_KEY_REV (sig) &&
		(sig->keyid[0] != kid[0] || sig->keyid[1] != kid[1]))
	      {
		int rc = check_revocation_keys (pk, sig);
		if (rc == 0)
		  {
		    *r_revoked = 2;
		    sig_to_revoke_info (sig, rinfo);


		    break;
		  }
		else if (rc == G10ERR_NO_PUBKEY)
		  pk->flags.maybe_revoked = 1;


	      }
	  }
      }


  signode = uidnode = NULL;
  sigdate = 0;
  for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY; k = k->next)
    {
      if (k->pkt->pkttype == PKT_USER_ID)
	{
	  if (uidnode && signode)
	    {
	      fixup_uidnode (uidnode, signode, keytimestamp);
	      pk->flags.valid = 1;
	    }
	  uidnode = k;
	  signode = NULL;
	  sigdate = 0;
	}
      else if (k->pkt->pkttype == PKT_SIGNATURE && uidnode)
	{
	  PKT_signature *sig = k->pkt->pkt.signature;
	  if (sig->keyid[0] == kid[0] && sig->keyid[1] == kid[1])
	    {
	      if (check_key_signature (keyblock, k, NULL))
		;
	      else if ((IS_UID_SIG (sig) || IS_UID_REV (sig))
		       && sig->timestamp >= sigdate)
		{


		  sigdate = sig->timestamp;
		  signode = k;
		  signode->pkt->pkt.signature->flags.chosen_selfsig = 0;
		  if (sig->version > sigversion)
		    sigversion = sig->version;
		}
	    }
	}
    }
  if (uidnode && signode)
    {
      fixup_uidnode (uidnode, signode, keytimestamp);
      pk->flags.valid = 1;
    }


  if (!pk->flags.valid && opt.allow_non_selfsigned_uid)
    {
      if (opt.verbose)
	log_info (_("Invalid key %s made valid by"
		    " --allow-non-selfsigned-uid\n"), keystr_from_pk (pk));
      pk->flags.valid = 1;
    }


  if (!pk->flags.valid)
    {
      uidnode = NULL;

      for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY;
	   k = k->next)
	{
	  if (k->pkt->pkttype == PKT_USER_ID)
	    uidnode = k;
	  else if (k->pkt->pkttype == PKT_SIGNATURE && uidnode)
	    {
	      PKT_signature *sig = k->pkt->pkt.signature;

	      if (sig->keyid[0] != kid[0] || sig->keyid[1] != kid[1])
		{
		  PKT_public_key *ultimate_pk;

		  ultimate_pk = xmalloc_clear (sizeof (*ultimate_pk));


		  if (get_pubkey_fast (ultimate_pk, sig->keyid) == 0
		      && check_key_signature2 (keyblock, k, ultimate_pk,
					       NULL, NULL, NULL, NULL) == 0
		      && get_ownertrust (ultimate_pk) == TRUST_ULTIMATE)
		    {
		      free_public_key (ultimate_pk);
		      pk->flags.valid = 1;
		      break;
		    }

		  free_public_key (ultimate_pk);
		}
	    }
	}
    }


  pk->selfsigversion = sigversion;


  if (!key_usage)
    {

      uiddate = 0;
      for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY;
	   k = k->next)
	{
	  if (k->pkt->pkttype == PKT_USER_ID)
	    {
	      PKT_user_id *uid = k->pkt->pkt.user_id;
	      if (uid->help_key_usage && uid->created > uiddate)
		{
		  key_usage = uid->help_key_usage;
		  uiddate = uid->created;
		}
	    }
	}
    }
  if (!key_usage)
    {

      key_usage = openpgp_pk_algo_usage (pk->pubkey_algo);
    }
  else
    {

      int x = openpgp_pk_algo_usage (pk->pubkey_algo);
      if (x)
	key_usage &= x;
    }


  pk->pubkey_usage = key_usage | PUBKEY_USAGE_CERT;

  if (!key_expire_seen)
    {


      uiddate = 0;
      for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY;
	   k = k->next)
	{
	  if (k->pkt->pkttype == PKT_USER_ID)
	    {
	      PKT_user_id *uid = k->pkt->pkt.user_id;
	      if (uid->help_key_expire && uid->created > uiddate)
		{
		  key_expire = uid->help_key_expire;
		  uiddate = uid->created;
		}
	    }
	}
    }


  if (key_expire == 0
      || (pk->max_expiredate && key_expire > pk->max_expiredate))
    key_expire = pk->max_expiredate;

  pk->has_expired = key_expire >= curtime ? 0 : key_expire;
  pk->expiredate = key_expire;


  uiddate = uiddate2 = 0;
  uidnode = uidnode2 = NULL;
  for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY; k = k->next)
    {
      if (k->pkt->pkttype == PKT_USER_ID && !k->pkt->pkt.user_id->attrib_data)
	{
	  PKT_user_id *uid = k->pkt->pkt.user_id;
	  if (uid->is_primary)
	    {
	      if (uid->created > uiddate)
		{
		  uiddate = uid->created;
		  uidnode = k;
		}
	      else if (uid->created == uiddate && uidnode)
		{


		  if (cmp_user_ids (uid, uidnode->pkt->pkt.user_id) > 0)
		    uidnode = k;
		}
	    }
	  else
	    {
	      if (uid->created > uiddate2)
		{
		  uiddate2 = uid->created;
		  uidnode2 = k;
		}
	      else if (uid->created == uiddate2 && uidnode2)
		{
		  if (cmp_user_ids (uid, uidnode2->pkt->pkt.user_id) > 0)
		    uidnode2 = k;
		}
	    }
	}
    }
  if (uidnode)
    {
      for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY;
	   k = k->next)
	{
	  if (k->pkt->pkttype == PKT_USER_ID &&
	      !k->pkt->pkt.user_id->attrib_data)
	    {
	      PKT_user_id *uid = k->pkt->pkt.user_id;
	      if (k != uidnode)
		uid->is_primary = 0;
	    }
	}
    }
  else if (uidnode2)
    {


      uidnode2->pkt->pkt.user_id->is_primary = 1;
    }
  else
    {


      uidnode = NULL;

      for (k = keyblock; k && k->pkt->pkttype != PKT_PUBLIC_SUBKEY;
	   k = k->next)
	{
	  if (k->pkt->pkttype == PKT_USER_ID
	      && !k->pkt->pkt.user_id->attrib_data)
	    {
	      if (!uidnode)
		{
		  uidnode = k;
		  uidnode->pkt->pkt.user_id->is_primary = 1;
		  continue;
		}
	      else
		{
		  if (cmp_user_ids (k->pkt->pkt.user_id,
				    uidnode->pkt->pkt.user_id) > 0)
		    {
		      uidnode->pkt->pkt.user_id->is_primary = 0;
		      uidnode = k;
		      uidnode->pkt->pkt.user_id->is_primary = 1;
		    }
		  else
		    k->pkt->pkt.user_id->is_primary = 0;

		}
	    }
	}
    }
}
