open_clientsock(char * address, int port)
{
  struct sockaddr_in servadr;
  int client_handle;


  if ((client_handle = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    exit_fatal ("Error opening socket Abort !");


  initaddr (&servadr,address,port);

  if (connect(client_handle,(struct sockaddr *) &servadr,
       sizeof (struct sockaddr)) == -1)
	  exit_fatal ("connect failed Abort !");
  return client_handle;
}
