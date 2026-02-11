ooSetCmdFDSETs(struct pollfd *pfds, int *nfds)
{
   if(gH323ep.cmdSock)
   {
      pfds[*nfds].fd = gH323ep.cmdSock;
      pfds[*nfds].events = POLLIN;
      (*nfds)++;
   }

   return OO_OK;

}
