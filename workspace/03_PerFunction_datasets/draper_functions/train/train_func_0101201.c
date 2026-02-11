fill_cmd_set_power_cycle_interval (uint8_t interval,
                                   fiid_obj_t obj_cmd_rq)
{
  if (!fiid_obj_valid (obj_cmd_rq))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd_rq, tmpl_cmd_set_power_cycle_interval_rq) < 0)
    {
      ERRNO_TRACE (errno);
      return (-1);
    }

  FILL_FIID_OBJ_CLEAR (obj_cmd_rq);

  FILL_FIID_OBJ_SET (obj_cmd_rq, "cmd", IPMI_CMD_SET_POWER_CYCLE_INTERVAL);
  FILL_FIID_OBJ_SET (obj_cmd_rq, "interval", interval);
  return (0);
}
