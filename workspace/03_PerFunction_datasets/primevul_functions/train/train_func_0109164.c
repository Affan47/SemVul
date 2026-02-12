my_bool handle_local_infile(MYSQL *mysql, const char *net_filename)
{
  my_bool result= 1;
  uint packet_length=MY_ALIGN(mysql->net.max_packet-16,IO_SIZE);
  NET *net= &mysql->net;
  int readcount;
  void *li_ptr;
  char *buf;
  struct st_mysql_options *options= &mysql->options;
  DBUG_ENTER("handle_local_infile");


  if (!(options->local_infile_init &&
	options->local_infile_read &&
	options->local_infile_end &&
	options->local_infile_error))
  {

    mysql_set_local_infile_default(mysql);
  }


  if (!(buf=my_malloc(packet_length, MYF(0))))
  {
    set_mysql_error(mysql, CR_OUT_OF_MEMORY, unknown_sqlstate);
    DBUG_RETURN(1);
  }


  if ((*options->local_infile_init)(&li_ptr, net_filename,
    options->local_infile_userdata))
  {
    (void) my_net_write(net,(const uchar*) "",0);
    net_flush(net);
    strmov(net->sqlstate, unknown_sqlstate);
    net->last_errno=
      (*options->local_infile_error)(li_ptr,
                                     net->last_error,
                                     sizeof(net->last_error)-1);
    goto err;
  }


  while ((readcount =
	  (*options->local_infile_read)(li_ptr, buf,
					packet_length)) > 0)
  {
    if (my_net_write(net, (uchar*) buf, readcount))
    {
      DBUG_PRINT("error",
		 ("Lost connection to MySQL server during LOAD DATA of local file"));
      set_mysql_error(mysql, CR_SERVER_LOST, unknown_sqlstate);
      goto err;
    }
  }


  if (my_net_write(net, (const uchar*) "", 0) || net_flush(net))
  {
    set_mysql_error(mysql, CR_SERVER_LOST, unknown_sqlstate);
    goto err;
  }

  if (readcount < 0)
  {
    net->last_errno=
      (*options->local_infile_error)(li_ptr,
                                     net->last_error,
                                     sizeof(net->last_error)-1);
    goto err;
  }

  result=0;

err:

  (*options->local_infile_end)(li_ptr);
  my_free(buf);
  DBUG_RETURN(result);
}
