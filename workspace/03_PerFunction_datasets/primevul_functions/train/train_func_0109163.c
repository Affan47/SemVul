static void fetch_result_str(MYSQL_BIND *param,
                             MYSQL_FIELD *field __attribute__((unused)),
                             uchar **row)
{
  ulong length= net_field_length(row);
  ulong copy_length= min(length, param->buffer_length);
  memcpy(param->buffer, (char *)*row, copy_length);

  if (copy_length != param->buffer_length)
    ((uchar *)param->buffer)[copy_length]= '\0';
  *param->length= length;
  *param->error= copy_length < length;
  *row+= length;
}
