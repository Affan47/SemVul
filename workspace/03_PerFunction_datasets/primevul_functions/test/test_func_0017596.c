router_parse_directory(const char *str)
{
  directory_token_t *tok;
  char digest[DIGEST_LEN];
  time_t published_on;
  int r;
  const char *end, *cp, *str_dup = str;
  smartlist_t *tokens = NULL;
  crypto_pk_env_t *declared_key = NULL;
  memarea_t *area = memarea_new();


  if (router_get_dir_hash(str, digest)) {
    log_warn(LD_DIR, "Unable to compute digest of directory");
    goto err;
  }
  log_debug(LD_DIR,"Received directory hashes to %s",hex_str(digest,4));


  cp = str;
  while (cp && (end = strstr(cp+1, "\ndirectory-signature")))
    cp = end;
  if (cp == str || !cp) {
    log_warn(LD_DIR, "No signature found on directory."); goto err;
  }
  ++cp;
  tokens = smartlist_create();
  if (tokenize_string(area,cp,strchr(cp,'\0'),tokens,dir_token_table,0)) {
    log_warn(LD_DIR, "Error tokenizing directory signature"); goto err;
  }
  if (smartlist_len(tokens) != 1) {
    log_warn(LD_DIR, "Unexpected number of tokens in signature"); goto err;
  }
  tok=smartlist_get(tokens,0);
  if (tok->tp != K_DIRECTORY_SIGNATURE) {
    log_warn(LD_DIR,"Expected a single directory signature"); goto err;
  }
  declared_key = find_dir_signing_key(str, str+strlen(str));
  note_crypto_pk_op(VERIFY_DIR);
  if (check_signature_token(digest, DIGEST_LEN, tok, declared_key,
                            CST_CHECK_AUTHORITY, "directory")<0)
    goto err;

  SMARTLIST_FOREACH(tokens, directory_token_t *, t, token_clear(t));
  smartlist_clear(tokens);
  memarea_clear(area);


  if ((end = strstr(str,"\nrouter "))) {
    ++end;
  } else if ((end = strstr(str, "\ndirectory-signature"))) {
    ++end;
  } else {
    end = str + strlen(str);
  }

  if (tokenize_string(area,str,end,tokens,dir_token_table,0)) {
    log_warn(LD_DIR, "Error tokenizing directory"); goto err;
  }

  tok = find_by_keyword(tokens, K_PUBLISHED);
  tor_assert(tok->n_args == 1);

  if (parse_iso_time(tok->args[0], &published_on) < 0) {
     goto err;
  }


  if (directory_caches_v1_dir_info(get_options()) &&
      !authdir_mode_v1(get_options()))
    dirserv_set_cached_directory(str, published_on, 0);

  r = 0;
  goto done;
 err:
  dump_desc(str_dup, "v1 directory");
  r = -1;
 done:
  if (declared_key) crypto_free_pk_env(declared_key);
  if (tokens) {
    SMARTLIST_FOREACH(tokens, directory_token_t *, t, token_clear(t));
    smartlist_free(tokens);
  }
  if (area) {
    DUMP_AREA(area, "v1 directory");
    memarea_drop_all(area);
  }
  return r;
}
