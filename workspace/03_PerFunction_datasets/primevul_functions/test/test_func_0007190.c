deinit_authz(void *data)
{

  authz_pool = NULL;
  filtered_pool = NULL;
  authz_pool_initialized = FALSE;
  return APR_SUCCESS;
}
