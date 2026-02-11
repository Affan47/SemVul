run_cmd_args (ipmi_oem_state_data_t *state_data)
{
  struct ipmi_oem_arguments *args;
  int rv = -1;

  assert (state_data);

  args = state_data->prog_data->args;


  assert (!args->list);
  assert (args->oem_id);
  assert (strcasecmp (args->oem_id, "list"));
  assert (strcasecmp (args->oem_id, "help"));

  if (args->sdr.flush_cache)
    return (_flush_cache (state_data));

  if (_run_oem_cmd (state_data) < 0)
    goto cleanup;

  rv = 0;
 cleanup:
  return (rv);
}
