ipmi_sdr_parse_product_id (ipmi_sdr_parse_ctx_t ctx,
                           const void *sdr_record,
                           unsigned int sdr_record_len,
                           uint16_t *product_id)
{
  fiid_obj_t obj_sdr_record = NULL;
  uint32_t acceptable_record_types;
  uint64_t val;
  int rv = -1;

  if (!ctx || ctx->magic != IPMI_SDR_PARSE_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sdr_parse_ctx_errormsg (ctx), ipmi_sdr_parse_ctx_errnum (ctx));
      return (-1);
    }

  if (!sdr_record || !sdr_record_len)
    {
      SDR_PARSE_SET_ERRNUM (ctx, IPMI_SDR_PARSE_ERR_PARAMETERS);
      return (-1);
    }

  acceptable_record_types = IPMI_SDR_PARSE_RECORD_TYPE_MANAGEMENT_CONTROLLER_CONFIRMATION_RECORD;

  if (!(obj_sdr_record = _sdr_record_get_common (ctx,
                                                 sdr_record,
                                                 sdr_record_len,
                                                 acceptable_record_types)))
    goto cleanup;

  if (product_id)
    {
      if (FIID_OBJ_GET (obj_sdr_record,
                        "product_id",
                        &val) < 0)
        {
          SDR_PARSE_FIID_OBJECT_ERROR_TO_SDR_PARSE_ERRNUM (ctx, obj_sdr_record);
          goto cleanup;
        }
      *product_id = val;
    }

  rv = 0;
  ctx->errnum = IPMI_SDR_PARSE_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_sdr_record);
  return (rv);
}
