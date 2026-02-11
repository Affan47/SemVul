fill_cmd_get_lan_configuration_parameters (uint8_t channel_number,
                                           uint8_t get_parameter,
                                           uint8_t parameter_selector,
                                           uint8_t set_selector,
                                           uint8_t block_selector,
                                           fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_CHANNEL_NUMBER_VALID (channel_number)
      || !IPMI_GET_LAN_PARAMETER_VALID (get_parameter)
      || (!IPMI_LAN_CONFIGURATION_PARAMETER_SELECTOR_VALID (parameter_selector)
          && !IPMI_LAN_CONFIGURATION_PARAMETER_SELECTOR_IS_OEM (parameter_selector))
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_get_lan_configuration_parameters_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_GET_LAN_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "channel_number", channel_number);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "get_parameter", get_parameter);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", parameter_selector);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "set_selector", set_selector);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "block_selector", block_selector);

  return (0);
}
