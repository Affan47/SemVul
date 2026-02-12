premerge_public_with_secret (KBNODE pubblock, KBNODE secblock)
{
  KBNODE last, pub;

  assert (pubblock->pkt->pkttype == PKT_PUBLIC_KEY);
  assert (secblock->pkt->pkttype == PKT_SECRET_KEY);

  for (pub = pubblock, last = NULL; pub; last = pub, pub = pub->next)
    {
      pub->flag &= ~3;
      if (pub->pkt->pkttype == PKT_PUBLIC_SUBKEY)
	{
	  KBNODE sec;
	  PKT_public_key *pk = pub->pkt->pkt.public_key;

	  for (sec = secblock->next; sec; sec = sec->next)
	    {
	      if (sec->pkt->pkttype == PKT_SECRET_SUBKEY)
		{
		  PKT_secret_key *sk = sec->pkt->pkt.secret_key;
		  if (!cmp_public_secret_key (pk, sk))
		    {
		      if (sk->protect.s2k.mode == 1001)
			{


			  pk->pubkey_usage &= ~(PUBKEY_USAGE_SIG
						| PUBKEY_USAGE_AUTH);
			}

		      pub->flag |= (sec->flag & 3);
		      break;
		    }
		}
	    }
	  if (!sec)
	    {
	      KBNODE next, ll;

	      if (opt.verbose)
		log_info (_("no secret subkey"
			    " for public subkey %s - ignoring\n"),
			  keystr_from_pk (pk));

	      assert (last);

	      for (next = pub->next, ll = pub;
		   next && next->pkt->pkttype != PKT_PUBLIC_SUBKEY;
		   ll = next, next = next->next)
		;

	      last->next = next;

	      ll->next = NULL;
	      release_kbnode (pub);

	      pub = last;
	    }
	}
    }


  pubblock->flag |= (secblock->flag & 3);
}
