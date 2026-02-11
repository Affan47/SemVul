GetAdapterType(void)
{
  cec_adapter_type type(ADAPTERTYPE_UNKNOWN);
  if (m_commands)
    type = (cec_adapter_type)m_commands->GetPersistedAdapterType();
  if (type == ADAPTERTYPE_UNKNOWN && IsOpen())
    type = (cec_adapter_type)m_commands->RequestAdapterType();

  return type;
}
