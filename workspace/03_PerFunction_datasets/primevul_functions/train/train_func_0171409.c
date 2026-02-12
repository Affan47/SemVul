void print_keydup_error(TABLE *table, KEY *key, const char *msg, myf errflag)
{

  char key_buff[MAX_KEY_LENGTH];
  String str(key_buff,sizeof(key_buff),system_charset_info);

  if (key == NULL)
  {


    my_printf_error(ER_DUP_ENTRY, msg, errflag, "", "*UNKNOWN*");
  }
  else
  {
    if (key->algorithm == HA_KEY_ALG_LONG_HASH)
      setup_keyinfo_hash(key);

    key_unpack(&str,table, key);
    uint max_length=MYSQL_ERRMSG_SIZE-(uint) strlen(msg);
    if (str.length() >= max_length)
    {
      str.length(max_length-4);
      str.append(STRING_WITH_LEN("..."));
    }
    my_printf_error(ER_DUP_ENTRY, msg, errflag, str.c_ptr_safe(),
                    key->name.str);
    if (key->algorithm == HA_KEY_ALG_LONG_HASH)
      re_setup_keyinfo_hash(key);
  }
}
