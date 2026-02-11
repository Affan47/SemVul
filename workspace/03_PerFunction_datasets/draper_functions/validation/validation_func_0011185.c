_pu_start_of_path(const char *string, int back_from)
{
  int i, j;


  if(!string || back_from < 0) {
    errno = EINVAL;
    return NULL;
  };


  for(i=back_from-1; i>=0; i--) {
    int c = string[i];


    if(isspace((int)(unsigned char)c)) {


      if(i==0)
        break;


      for(j=i-1; j>=0 && string[j]=='\\'; j--)
	;


      if((i - 1 - j) % 2 == 0)
	break;
    };
  };
  return (char *)string + i + 1;
}
