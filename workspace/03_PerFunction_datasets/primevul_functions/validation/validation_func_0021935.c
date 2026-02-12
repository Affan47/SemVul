tape_buffered_peek (char *peek_buf, int in_des, int num_bytes)
{
  long tmp_input_size;
  long got_bytes;
  char *append_buf;

#ifdef BROKEN_LONG_TAPE_DRIVER


  if (input_is_special
      && ( (input_bytes_before_lseek += num_bytes) >= 1073741824L) )
    {
      lseek(in_des, 0L, SEEK_SET);
      input_bytes_before_lseek = 0;
    }
#endif

  while (input_size < num_bytes)
    {
      append_buf = in_buff + input_size;
      if ( (append_buf - input_buffer) >= input_buffer_size)
	{


	  int half;
	  half = input_buffer_size / 2;
	  memmove (input_buffer, input_buffer + half, half);
	  in_buff = in_buff - half;
	  append_buf = append_buf - half;
	}
      tmp_input_size = rmtread (in_des, append_buf, io_block_size);
      if (tmp_input_size == 0)
	{
	  if (input_is_special)
	    {
	      get_next_reel (in_des);
	      tmp_input_size = rmtread (in_des, append_buf, io_block_size);
	    }
	  else
	    break;
	}
      if (tmp_input_size < 0)
	error (PAXEXIT_FAILURE, errno, _("read error"));
      input_bytes += tmp_input_size;
      input_size += tmp_input_size;
    }
  if (num_bytes <= input_size)
    got_bytes = num_bytes;
  else
    got_bytes = input_size;
  memcpy (peek_buf, in_buff, (unsigned) got_bytes);
  return got_bytes;
}
