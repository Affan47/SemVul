Emit_IOType_defs(){

  int   i;
  char  buf[REG_MAX_MSG_SIZE];
  char *pbuf;
  int   nbytes, bytes_left;


  if (IOTypes_table.num_registered == 0) return REG_SUCCESS;


  bytes_left = REG_MAX_MSG_SIZE;
  pbuf = buf;
  Write_xml_header(&pbuf);

  nbytes = sprintf(pbuf, "<IOType_defs>\n");

  pbuf += nbytes;
  bytes_left -= nbytes;

  for(i=0; i<IOTypes_table.max_entries; i++){

    if(IOTypes_table.io_def[i].handle != REG_IODEF_HANDLE_NOTSET){


      strncpy((char *)Global_scratch_buffer,
	      IOTypes_table.io_def[i].label,
	      REG_SCRATCH_BUFFER_SIZE);

      nbytes = snprintf(pbuf, bytes_left, "<IOType>\n"
			"<Label>%s</Label>\n"
			"<Handle>%d</Handle>\n",
			trimWhiteSpace((char *)Global_scratch_buffer),
			IOTypes_table.io_def[i].handle);

#ifdef REG_DEBUG

      if((nbytes >= (bytes_left-1)) || (nbytes < 1)){

	fprintf(stderr, "STEER: Emit_IOType_defs: message exceeds max. "
		"msg. size of %d bytes\n", REG_MAX_MSG_SIZE);
	return REG_FAILURE;
      }
#endif
      pbuf += nbytes;
      bytes_left -= nbytes;

      switch(IOTypes_table.io_def[i].direction){

      case REG_IO_IN:
        nbytes = snprintf(pbuf, bytes_left, "<Direction>IN</Direction>\n");
	break;

      case REG_IO_OUT:
        nbytes = snprintf(pbuf, bytes_left, "<Direction>OUT</Direction>\n");
	break;

      default:
#ifdef REG_DEBUG
	fprintf(stderr,
		"STEER: Emit_IOType_defs: Unrecognised IOType direction\n");
#endif
	return REG_FAILURE;
      }
      pbuf += nbytes;
      bytes_left -= nbytes;


      nbytes = snprintf(pbuf, bytes_left, "<Freq_handle>%d</Freq_handle>\n",
			IOTypes_table.io_def[i].freq_param_handle);
#ifdef REG_DEBUG

      if((nbytes >= (bytes_left-1)) || (nbytes < 1)){

	fprintf(stderr, "STEER: Emit_IOType_defs: message exceeds max. "
		"msg. size of %d bytes\n", REG_MAX_MSG_SIZE);
	return REG_FAILURE;
      }
#endif
      pbuf += nbytes;
      bytes_left -= nbytes;

      Get_IOType_address_impl(i, &pbuf, &bytes_left);

      nbytes = snprintf(pbuf, bytes_left, "</IOType>\n");
      pbuf += nbytes;
      bytes_left -= nbytes;
    }
  }

  nbytes = snprintf(pbuf, bytes_left, "</IOType_defs>\n");
  pbuf += nbytes;
  bytes_left -= nbytes;

  if(Write_xml_footer(&pbuf, bytes_left) == REG_SUCCESS){


    return Send_status_msg(buf);
  }

  fprintf(stderr, "STEER: Emit_IOType_defs: ran out of space for footer\n");
  return REG_FAILURE;
}
