mxf_timestamp_write (const MXFTimestamp * timestamp, guint8 * data)
{
  GST_WRITE_UINT16_BE (data, timestamp->year);
  GST_WRITE_UINT8 (data + 2, timestamp->month);
  GST_WRITE_UINT8 (data + 3, timestamp->day);
  GST_WRITE_UINT8 (data + 4, timestamp->hour);
  GST_WRITE_UINT8 (data + 5, timestamp->minute);
  GST_WRITE_UINT8 (data + 6, timestamp->second);
  GST_WRITE_UINT8 (data + 7, (timestamp->msecond * 256) / 1000);
}
