rend_valid_v2_service_id(const char *query)
{

#define REND_SERVICE_ID_LEN_BASE32 16

  if (strlen(query) != REND_SERVICE_ID_LEN_BASE32)
    return 0;

  if (strspn(query, BASE32_CHARS) != REND_SERVICE_ID_LEN_BASE32)
    return 0;

  return 1;
}
