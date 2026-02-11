fill_cmd_set_lan_configuration_parameters_bad_password_threshold (uint8_t channel_number,
                                                                  uint8_t user_disabled_event_message,
                                                                  uint8_t bad_password_threshold_number,
                                                                  uint16_t attempt_count_reset_interval,
                                                                  uint16_t user_lockout_interval,
                                                                  fiid_obj_t obj_cmd_rq)
{
  if (!IPMI_CHANNEL_NUMBER_VALID (channel_number)
      || !IPMI_USER_DISABLED_EVENT_MESSAGE_VALID (user_disabled_event_message)
      || !fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_lan_configuration_parameters_bad_password_threshold_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_LAN_CONFIGURATION_PARAMETERS);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "channel_number", channel_number);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved1", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "parameter_selector", IPMI_LAN_CONFIGURATION_PARAMETER_BAD_PASSWORD_THRESHOLD);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "user_disabled_event_message", user_disabled_event_message);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "reserved2", 0);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "bad_password_threshold_number", bad_password_threshold_number);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "attempt_count_reset_interval", attempt_count_reset_interval);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "user_lockout_interval", user_lockout_interval);

  return (0);
}
