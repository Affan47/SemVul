sic_init_entry(Sic_entry *oic, char *digest, char *username, Ic_token *token)
{
  Sic_entry *sic;

  if (oic == NULL)
	sic = ALLOC(Sic_entry);
  else
	sic = oic;

  sic->state = IC_UNCHANGED;
  sic->alg = PASSWD_ALG_NONE;
  sic->username = username;
  sic->friendly_id = icx_friendly_identifier(token->ppid, 1);
  sic->pubkey_modulus = ds_buf(token->modulus);
  sic->pubkey_exponent = ds_buf(token->exponent);
  sic->digest = digest;
  sic->private = NULL;

  return(sic);
}
