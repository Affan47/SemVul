ip_listen(char *ip_addr,int port,int sock_type,int max_fd,int fd_array[])
{
   struct addrinfo hints,*res,*res0;
   char port_str[20],*addr;
   int nsock,error,i;
   int reuse = 1;

   for(i=0;i<max_fd;i++)
      fd_array[i] = -1;

   memset(&hints,0,sizeof(hints));
   hints.ai_family = PF_UNSPEC;
   hints.ai_socktype = sock_type;
   hints.ai_flags = AI_PASSIVE;

   snprintf(port_str,sizeof(port_str),"%d",port);
   addr = (ip_addr && strlen(ip_addr)) ? ip_addr : NULL;

   if ((error = getaddrinfo(addr,port_str,&hints,&res0)) != 0) {
      fprintf(stderr,"ip_listen: %s", gai_strerror(error));
      return(-1);
   }

   nsock = 0;
   for(res=res0;(res && (nsock < max_fd));res=res->ai_next)
   {
      if ((res->ai_family != PF_INET) && (res->ai_family != PF_INET6))
         continue;

      fd_array[nsock] = socket(res->ai_family,res->ai_socktype,
                               res->ai_protocol);

      if (fd_array[nsock] < 0)
         continue;

      setsockopt(fd_array[nsock],SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));

      if ((bind(fd_array[nsock],res->ai_addr,res->ai_addrlen) < 0) ||
          ((sock_type == SOCK_STREAM) && (listen(fd_array[nsock],5) < 0)))
      {
         close(fd_array[nsock]);
         fd_array[nsock] = -1;
         continue;
      }

      nsock++;
   }

   freeaddrinfo(res0);
   return(nsock);
}
