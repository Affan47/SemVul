avis_message_read (ByteBuffer *buffer, Message message, ElvinError *error)
{
  uint32_t type = byte_buffer_read_int32 (buffer, error);
  MessageFormat *format;

  memset (message, 0, MAX_MESSAGE_SIZE);

  if (elvin_error_occurred (error))
    return false;

  if ((format = message_format_for (type)) == NULL)
  {
    elvin_error_set (error, ELVIN_ERROR_PROTOCOL,
                     "Unknown message type: %u", type);

    return false;
  }

  message_type_of (message) = type;

  if (read_using_format (buffer, message + 4, format, error))
  {
    return true;
  } else
  {
    avis_message_free (message);

    return false;
  }
}
