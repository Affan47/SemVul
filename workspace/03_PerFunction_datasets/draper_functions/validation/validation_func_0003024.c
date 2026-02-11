RequestBuildDate(void)
{
  if (m_iBuildDate == CEC_FW_BUILD_UNKNOWN)
  {
#ifdef CEC_DEBUGGING
    LIB_CEC->AddLog(CEC_LOG_DEBUG, "requesting firmware build date");
#endif

    cec_datapacket response = RequestSetting(MSGCODE_GET_BUILDDATE);
    if (response.size == 4)
      m_iBuildDate = (uint32_t)response[0] << 24 | (uint32_t)response[1] << 16 | (uint32_t)response[2] << 8 | (uint32_t)response[3];
  }
  return m_iBuildDate;
}
