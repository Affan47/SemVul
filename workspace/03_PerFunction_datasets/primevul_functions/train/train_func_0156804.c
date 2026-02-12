guardfraction_file_parse_guard_line(const char *guard_line,
                                    smartlist_t *vote_routerstatuses,
                                    char **err_msg)
{
  char guard_id[DIGEST_LEN];
  uint32_t guardfraction;
  char *inputs_tmp = NULL;
  int num_ok = 1;

  smartlist_t *sl = smartlist_new();
  int retval = -1;

  tor_assert(err_msg);


  smartlist_split_string(sl, guard_line, " ",
                         SPLIT_SKIP_SPACE|SPLIT_IGNORE_BLANK, 3);
  if (smartlist_len(sl) < 3) {
    tor_asprintf(err_msg, "bad line '%s'", guard_line);
    goto done;
  }

  inputs_tmp = smartlist_get(sl, 0);
  if (strlen(inputs_tmp) != HEX_DIGEST_LEN ||
      base16_decode(guard_id, DIGEST_LEN,
                    inputs_tmp, HEX_DIGEST_LEN) != DIGEST_LEN) {
    tor_asprintf(err_msg, "bad digest '%s'", inputs_tmp);
    goto done;
  }

  inputs_tmp = smartlist_get(sl, 1);

  guardfraction =
    (uint32_t) tor_parse_long(inputs_tmp, 10, 0, 100, &num_ok, NULL);
  if (!num_ok) {
    tor_asprintf(err_msg, "wrong percentage '%s'", inputs_tmp);
    goto done;
  }


  if (vote_routerstatuses) {
    retval = guardfraction_line_apply(guard_id, guardfraction,
                                      vote_routerstatuses);
  } else {
    retval = 0;
  }

 done:

  SMARTLIST_FOREACH(sl, char *, cp, tor_free(cp));
  smartlist_free(sl);

  return retval;
}
