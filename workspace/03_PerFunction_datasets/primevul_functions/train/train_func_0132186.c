parse_extended_hostname(char *address, hostname_type_t *type_out)
{
  char *s;
  char *q;
  char query[HS_SERVICE_ADDR_LEN_BASE32+1];

  s = strrchr(address,'.');
  if (!s) {
    *type_out = NORMAL_HOSTNAME;
    goto success;
  }
  if (!strcmp(s+1,"exit")) {
    *s = 0;
    *type_out = EXIT_HOSTNAME;
    goto success;
  }
  if (strcmp(s+1,"onion")) {
    *type_out = NORMAL_HOSTNAME;
    goto success;
  }


  *s = 0;

  q = strrchr(address, '.');
  if (q == address) {
    *type_out = BAD_HOSTNAME;
    goto failed;
  }
  q = (NULL == q) ? address : q + 1;
  if (strlcpy(query, q, HS_SERVICE_ADDR_LEN_BASE32+1) >=
      HS_SERVICE_ADDR_LEN_BASE32+1) {
    *type_out = BAD_HOSTNAME;
    goto failed;
  }
  if (q != address) {
    memmove(address, q, strlen(q) + 1 );
  }

  if (strlen(query) == REND_SERVICE_ID_LEN_BASE32) {
    *type_out = ONION_V2_HOSTNAME;
    if (rend_valid_v2_service_id(query)) {
      goto success;
    }
    goto failed;
  }


  if (strlen(query) == HS_SERVICE_ADDR_LEN_BASE32) {
    *type_out = ONION_V3_HOSTNAME;
    if (hs_address_is_valid(query)) {
      goto success;
    }
    goto failed;
  }


  *type_out = BAD_HOSTNAME;
  goto failed;

 success:
  return true;
 failed:

  *s = '.';
  const bool is_onion = (*type_out == ONION_V2_HOSTNAME) ||
    (*type_out == ONION_V3_HOSTNAME);
  log_warn(LD_APP, "Invalid %shostname %s; rejecting",
           is_onion ? "onion " : "",
           safe_str_client(address));
  if (*type_out == ONION_V3_HOSTNAME) {
      *type_out = BAD_HOSTNAME;
  }
  return false;
}
