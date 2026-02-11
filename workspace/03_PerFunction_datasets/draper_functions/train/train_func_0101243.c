gst_asf_put_payload (guint8 * buf, AsfPayload * payload)
{
  GST_WRITE_UINT8 (buf, payload->stream_number);
  GST_WRITE_UINT8 (buf + 1, payload->media_obj_num);
  GST_WRITE_UINT32_LE (buf + 2, payload->offset_in_media_obj);
  GST_WRITE_UINT8 (buf + 6, payload->replicated_data_length);
  GST_WRITE_UINT32_LE (buf + 7, payload->media_object_size);
  GST_WRITE_UINT32_LE (buf + 11, payload->presentation_time);
  GST_WRITE_UINT16_LE (buf + 15, (guint16) GST_BUFFER_SIZE (payload->data));
  memcpy (buf + 17, GST_BUFFER_DATA (payload->data),
      GST_BUFFER_SIZE (payload->data));

  payload->packet_count++;
}
