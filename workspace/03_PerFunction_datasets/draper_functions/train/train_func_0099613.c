set_device (const Ekiga::AudioInputDevice & device)
{
  if ( ( device.type   == DEVICE_TYPE ) &&
       ( device.source == DEVICE_SOURCE) &&
       ( device.name   == DEVICE_NAME) ) {

    PTRACE(4, "GMAudioInputManager_null\tSetting Device " << device);
    current_state.device = device;
    return true;
  }
  return false;
}
