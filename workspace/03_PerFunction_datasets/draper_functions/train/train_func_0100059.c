ooGetLocalIPAddress(char * pIPAddrs)
{
   int ret;
   struct hostent *hp;
   struct ast_hostent phost;
   char hostname[100];

   if(pIPAddrs == NULL)
      return -1;
   ret = gethostname(hostname, 100);
   if(ret == 0)
   {
      if ((hp = ast_gethostbyname(hostname, &phost))) {
			if (hp->h_addrtype == AF_INET6) {
				struct in6_addr i;
				memcpy(&i, hp->h_addr, sizeof(i));
				strcpy(pIPAddrs, (inet_ntop(AF_INET6, &i,
				hostname, sizeof(hostname))) == NULL ? "::1" :
				inet_ntop(AF_INET6, &i, hostname, sizeof(hostname)));
			} else {
	  			struct in_addr i;
				memcpy(&i, hp->h_addr, sizeof(i));
			  	strcpy(pIPAddrs, (ast_inet_ntoa(i) == NULL) ? "127.0.0.1" : ast_inet_ntoa(i));
			}
      } else {
         return -1;
      }
   }
   else{
      return -1;
   }
   return ASN_OK;
}
