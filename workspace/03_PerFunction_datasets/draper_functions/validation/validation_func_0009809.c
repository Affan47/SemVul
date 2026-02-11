HandlePoll(cec_logical_address initiator, cec_logical_address destination)
{
  CCECBusDevice *device = m_busDevices->At(destination);
  if (device)
    device->HandlePollFrom(initiator);
}
