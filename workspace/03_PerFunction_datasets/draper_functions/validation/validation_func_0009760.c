wait_frame(char frame_id)
{
  int read_more = 1;
  int success = 0;
  int n;
  char target = frame_id;

  if(debug_flag){printf("%s: Looking for frametype 0x%.2x\n",name,target);}
  read_more = 1;
  while(read_more){
    n = read(sock,readbuf,1);
    if(debug_flag){printf("%s: Found frametype 0x%.2x\n",name,readbuf[0]);}
    if(readbuf[0] == target){
      read_more = 0;
      success = 1;
    }
    else{
      if(readbuf[0] == message_status){
	ignore_message_status();
	read_more = 1;
      }
      else{
	if(debug_flag){printf("%s: Got unexpected frame from switch\n",name);}
	read_more = 0;
	success = 0;
      }
    }
  }
  return(success);
}
