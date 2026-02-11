CecAlert(void *UNUSED(cbParam), const libcec_alert type, const libcec_parameter UNUSED(param))
{
  switch (type)
  {
  case CEC_ALERT_CONNECTION_LOST:
    if (!CReconnect::Get().IsRunning())
    {
      PrintToStdOut("Connection lost - trying to reconnect\n");
      CReconnect::Get().CreateThread(false);
    }
    break;
  default:
    break;
  }
  return 0;
}
