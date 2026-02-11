gst_rtp_speex_pay_parse_ident (GstRtpSPEEXPay * rtpspeexpay,
    const guint8 * data, guint size)
{
  guint32 version, header_size, rate, mode, nb_channels;
  GstBaseRTPPayload *payload;
  gchar *cstr;
  gboolean res;


  if (size < 36)
    goto too_small;

  if (!g_str_has_prefix ((const gchar *) data, "Speex   "))
    goto wrong_header;


  data += 28;

  version = GST_READ_UINT32_LE (data);
  if (version != 1)
    goto wrong_version;

  data += 4;

  header_size = GST_READ_UINT32_LE (data);
  if (header_size < 80)
    goto header_too_small;

  if (size < header_size)
    goto payload_too_small;

  data += 4;
  rate = GST_READ_UINT32_LE (data);
  data += 4;
  mode = GST_READ_UINT32_LE (data);
  data += 8;
  nb_channels = GST_READ_UINT32_LE (data);

  GST_DEBUG_OBJECT (rtpspeexpay, "rate %d, mode %d, nb_channels %d",
      rate, mode, nb_channels);

  payload = GST_BASE_RTP_PAYLOAD (rtpspeexpay);

  gst_basertppayload_set_options (payload, "audio", FALSE, "SPEEX", rate);
  cstr = g_strdup_printf ("%d", nb_channels);
  res = gst_basertppayload_set_outcaps (payload, "encoding-params",
      G_TYPE_STRING, cstr, NULL);
  g_free (cstr);

  return res;


too_small:
  {
    GST_DEBUG_OBJECT (rtpspeexpay,
        "ident packet too small, need at least 32 bytes");
    return FALSE;
  }
wrong_header:
  {
    GST_DEBUG_OBJECT (rtpspeexpay,
        "ident packet does not start with \"Speex   \"");
    return FALSE;
  }
wrong_version:
  {
    GST_DEBUG_OBJECT (rtpspeexpay, "can only handle version 1, have version %d",
        version);
    return FALSE;
  }
header_too_small:
  {
    GST_DEBUG_OBJECT (rtpspeexpay,
        "header size too small, need at least 80 bytes, " "got only %d",
        header_size);
    return FALSE;
  }
payload_too_small:
  {
    GST_DEBUG_OBJECT (rtpspeexpay,
        "payload too small, need at least %d bytes, got only %d", header_size,
        size);
    return FALSE;
  }
}
