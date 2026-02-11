net_store_data(const uchar *from, size_t length,
                              CHARSET_INFO *from_cs, CHARSET_INFO *to_cs)
{
  uint dummy_errors;

  uint conv_length= to_cs->mbmaxlen * length / from_cs->mbminlen;
  if (conv_length > 250)
  {


    return (convert->copy((const char*) from, length, from_cs,
                          to_cs, &dummy_errors) ||
            net_store_data((const uchar*) convert->ptr(), convert->length()));
  }

  ulong packet_length= packet->length();
  ulong new_length= packet_length + conv_length + 1;

  if (new_length > packet->alloced_length() && packet->realloc(new_length))
    return 1;

  char *length_pos= (char*) packet->ptr() + packet_length;
  char *to= length_pos + 1;

  to+= copy_and_convert(to, conv_length, to_cs,
                        (const char*) from, length, from_cs, &dummy_errors);

  net_store_length((uchar*) length_pos, to - length_pos - 1);
  packet->length((uint) (to - packet->ptr()));
  return 0;
}
