ecasv_cop_to_string(ECA_CONTROL_INTERFACE* eci)
{
  eci->command("cop-status");
  return(eci->last_string());
}
