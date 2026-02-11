_sel_parse_ctx_error_convert (ipmi_monitoring_ctx_t c)
{
  int errnum;

  assert (c);
  assert (c->magic == IPMI_MONITORING_MAGIC);
  assert (c->ipmi_ctx);
  assert (c->sel_parse_ctx);

  errnum = ipmi_sel_parse_ctx_errnum (c->sel_parse_ctx);


  if (errnum != IPMI_SEL_PARSE_ERR_CALLBACK_ERROR)
    {
      if (errnum == IPMI_SEL_PARSE_ERR_IPMI_ERROR)
        c->errnum = IPMI_MONITORING_ERR_IPMI_ERROR;
      else if (errnum == IPMI_SEL_PARSE_ERR_OUT_OF_MEMORY)
        c->errnum = IPMI_MONITORING_ERR_OUT_OF_MEMORY;
      else if (errnum == IPMI_SEL_PARSE_ERR_SYSTEM_ERROR)
        c->errnum = IPMI_MONITORING_ERR_SYSTEM_ERROR;
      else
        c->errnum = IPMI_MONITORING_ERR_INTERNAL_ERROR;
    }
}
