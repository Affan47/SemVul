OFCondition DcmSCP::setConfig(const DcmSCPConfig& config)
{
  if (isConnected())
  {
    return EC_IllegalCall;
  }
  m_cfg = DcmSharedSCPConfig( config );
  return EC_Normal;
}
