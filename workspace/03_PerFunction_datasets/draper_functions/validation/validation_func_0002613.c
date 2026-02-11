stp_set_string_parameter_n(stp_vars_t *v, const char *parameter,
			   const char *value, size_t bytes)
{
  stp_list_t *list = v->params[STP_PARAMETER_TYPE_STRING_LIST];
  if (value)
    stp_deprintf(STP_DBG_VARS, "stp_set_string_parameter(0x%p, %s, %s)\n",
		 (const void *) v, parameter, value);
  else
    stp_deprintf(STP_DBG_VARS, "stp_set_string_parameter(0x%p, %s)\n",
		 (const void *) v, parameter);
  set_raw_parameter(list, parameter, value, bytes,
		    STP_PARAMETER_TYPE_STRING_LIST);
  stp_set_verified(v, 0);
}
