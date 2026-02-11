_ipmi_monitoring_sdr_cache_delete (ipmi_monitoring_ctx_t c,
                                   const char *hostname,
                                   char *filename)
{
  assert (c);
  assert (c->magic == IPMI_MONITORING_MAGIC);
  assert (c->sdr_cache_ctx);
  assert (c->ipmi_ctx);

  if (ipmi_sdr_cache_delete (c->sdr_cache_ctx, filename) < 0)
    {
      if (ipmi_sdr_cache_ctx_errnum (c->sdr_cache_ctx) !=  IPMI_SDR_CACHE_ERR_FILENAME_INVALID)
        {
          IPMI_MONITORING_DEBUG (("ipmi_sdr_cache_delete: %s", ipmi_sdr_cache_ctx_errormsg (c->sdr_cache_ctx)));
          if (ipmi_sdr_cache_ctx_errnum (c->sdr_cache_ctx) == IPMI_SDR_CACHE_ERR_PERMISSION)
            c->errnum = IPMI_MONITORING_ERR_SDR_CACHE_PERMISSION;
          else
            c->errnum = IPMI_MONITORING_ERR_INTERNAL_ERROR;
          return (-1);
        }
    }

  return (0);
}
