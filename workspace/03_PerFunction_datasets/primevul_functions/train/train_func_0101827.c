static COMMANDS *find_command(char *name,char cmd_char)
{
  uint len;
  char *end;
  DBUG_ENTER("find_command");
  DBUG_PRINT("enter",("name: '%s'  char: %d", name ? name : "NULL", cmd_char));

  if (!name)
  {
    len=0;
    end=0;
  }
  else
  {
    while (my_isspace(charset_info,*name))
      name++;


    if (strstr(name, "\\g") || (strstr(name, delimiter) &&
                                !(strlen(name) >= 9 &&
                                  !my_strnncoll(&my_charset_latin1,
                                                (uchar*) name, 9,
                                                (const uchar*) "delimiter",
                                                9))))
      DBUG_RETURN((COMMANDS *) 0);
    if ((end=strcont(name," \t")))
    {
      len=(uint) (end - name);
      while (my_isspace(charset_info,*end))
	end++;
      if (!*end)
	end=0;
    }
    else
      len=(uint) strlen(name);
  }

  for (uint i= 0; commands[i].name; i++)
  {
    if (commands[i].func &&
	((name &&
	  !my_strnncoll(&my_charset_latin1, (uchar*)name, len,
				     (uchar*)commands[i].name,len) &&
	  !commands[i].name[len] &&
	  (!end || (end && commands[i].takes_params))) ||
	 (!name && commands[i].cmd_char == cmd_char)))
    {
      DBUG_PRINT("exit",("found command: %s", commands[i].name));
      DBUG_RETURN(&commands[i]);
    }
  }
  DBUG_RETURN((COMMANDS *) 0);
}
