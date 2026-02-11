IsActiveDeviceType(const cec_device_type type)
{
  CECDEVICEVEC activeDevices;
  if (m_processor)
    m_processor->GetDevices()->GetActive(activeDevices);
  CCECDeviceMap::FilterType(type, activeDevices);
  return !activeDevices.empty();
}
