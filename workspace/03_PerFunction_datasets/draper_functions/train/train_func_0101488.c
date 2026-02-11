ToLogicalAddresses(const CECDEVICEVEC &devices)
{
  cec_logical_addresses addresses;
  addresses.Clear();
  for (CECDEVICEVEC::const_iterator it = devices.begin(); it != devices.end(); it++)
    addresses.Set((*it)->GetLogicalAddress());
  return addresses;
}
