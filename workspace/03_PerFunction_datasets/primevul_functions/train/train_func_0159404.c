receive_swallow_smtp(void)
{

if (message_ended >= END_NOTENDED)
  message_ended = read_message_data_smtp(NULL);
}
