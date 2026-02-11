hysteresis_threshold_checkout (const char *section_name,
                               struct config_keyvalue *kv,
                               void *arg)
{
  ipmi_sensors_config_state_data_t *state_data;
  uint8_t sdr_record[IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH];
  unsigned int sdr_record_len = IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;
  uint8_t positive_going_threshold_hysteresis_value;
  uint8_t negative_going_threshold_hysteresis_value;
  uint8_t value_raw;
  double value_calc;
  uint8_t hysteresis_support;
  uint8_t sensor_number;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (ipmi_sensors_config_state_data_t *)arg;

  if ((ret = get_sdr_record (state_data,
                             section_name,
                             sdr_record,
                             &sdr_record_len)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if (ipmi_sdr_parse_sensor_capabilities (state_data->sdr_parse_ctx,
                                          sdr_record,
                                          sdr_record_len,
                                          NULL,
                                          NULL,
                                          &hysteresis_support,
                                          NULL,
                                          NULL) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_sensor_capabilities: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      goto cleanup;
    }


  if (hysteresis_support != IPMI_SDR_READABLE_HYSTERESIS_SUPPORT
      && hysteresis_support != IPMI_SDR_READABLE_SETTABLE_HYSTERESIS_SUPPORT)
    {
      rv = CONFIG_ERR_NON_FATAL_ERROR;
      goto cleanup;
    }

  if (ipmi_sdr_parse_sensor_number (state_data->sdr_parse_ctx,
                                    sdr_record,
                                    sdr_record_len,
                                    &sensor_number) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_sensor_number: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      goto cleanup;
    }

  if ((ret = _get_hysteresis (state_data,
                              sensor_number,
                              &positive_going_threshold_hysteresis_value,
                              &negative_going_threshold_hysteresis_value)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if (!strcasecmp (kv->key->key_name, "Positive_Going_Threshold_Hysteresis"))
    value_raw = positive_going_threshold_hysteresis_value;
  else if (!strcasecmp (kv->key->key_name, "Negative_Going_Threshold_Hysteresis"))
    value_raw = negative_going_threshold_hysteresis_value;
  else

    goto cleanup;


  if (value_raw == 0)
    {
      if (config_section_update_keyvalue_output (state_data->pstate,
                                                 kv,
                                                 "None") < 0)
        goto cleanup;
    }
  else
    {
      if ((ret = _decode_value (state_data,
                                sdr_record,
                                sdr_record_len,
                                value_raw,
                                &value_calc)) != CONFIG_ERR_SUCCESS)
        {
          rv = ret;
          goto cleanup;
        }

      if (config_section_update_keyvalue_output_double (state_data->pstate,
                                                        kv,
                                                        value_calc) < 0)
        goto cleanup;
    }

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  return (rv);
}
