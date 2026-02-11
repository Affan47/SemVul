do_we_trust_pre( PKT_public_key *pk, unsigned int trustlevel )
{
  int rc;

  rc = do_we_trust( pk, trustlevel );

  if( !opt.batch && !rc )
    {
      print_pubkey_info(NULL,pk);
      print_fingerprint (pk, NULL, 2);
      tty_printf("\n");

      tty_printf(
	       _("It is NOT certain that the key belongs to the person named\n"
		 "in the user ID.  If you *really* know what you are doing,\n"
		 "you may answer the next question with yes.\n"));

      tty_printf("\n");

      if( cpr_get_answer_is_yes("untrusted_key.override",
				_("Use this key anyway? (y/N) "))  )
	rc = 1;


    }

  return rc;
}
