_ipmi_monitoring_sel_parse_date_range (ipmi_sel_parse_ctx_t ctx, void *callback_data)
{
  struct sel_parse_data *spd;
  uint8_t record_type;
  int record_type_class;

  assert (ctx);
  assert (callback_data);

  spd = (struct sel_parse_data *)callback_data;

  if (ipmi_sel_parse_read_record_type (spd->c->sel_parse_ctx, &record_type) < 0)
    {
      IPMI_MONITORING_DEBUG (("ipmi_sel_parse_read_record_id: %s",
                              ipmi_sel_parse_ctx_errnum (spd->c->sel_parse_ctx)));
      _sel_parse_ctx_error_convert (spd->c);
      return (-1);
    }


  if (spd->sel_flags & IPMI_MONITORING_SEL_FLAGS_ASSUME_SYSTEM_EVENT_RECORD
      && !IPMI_SEL_RECORD_TYPE_VALID (record_type))
    record_type = IPMI_SEL_RECORD_TYPE_SYSTEM_EVENT_RECORD;

  record_type_class = ipmi_sel_record_type_class (record_type);

  if (record_type_class == IPMI_SEL_RECORD_TYPE_CLASS_SYSTEM_EVENT_RECORD
      || record_type_class == IPMI_SEL_RECORD_TYPE_CLASS_TIMESTAMPED_OEM_RECORD)
    {
      uint32_t timestamp;

      if (ipmi_sel_parse_read_timestamp (spd->c->sel_parse_ctx, &timestamp) < 0)
        {
          IPMI_MONITORING_DEBUG (("ipmi_sel_parse_read_timestamp: %s",
                                  ipmi_sel_parse_ctx_errnum (spd->c->sel_parse_ctx)));
          _sel_parse_ctx_error_convert (spd->c);
          return (-1);
        }

      if (timestamp >= spd->date_begin
          && timestamp <= spd->date_end)
        {
          if (_store_sel_record (spd->c, spd->sel_flags) < 0)
            return (-1);
        }
    }

  return (0);
}
