root_recv_buffer(int sock, int *op, char *buffer, int buflen)
{


  int recv1 = 0;
  int len;
  int status;
  char recbuf[MAXLEN];

  status = NET_RecvRaw(sock,&len,4);
#ifdef DEBUG
  printf("Recv: status from rec is %d\n",status);
#endif
  if (status < 0) {
    return status;
  }
  recv1 += status;

  len = ntohl(len);
#ifdef DEBUG
  printf ("Recv: length is %d\n",len);
#endif


  len -= 4;
  status = NET_RecvRaw(sock,op,4);
  if (status < 0) {
    return status;
  }

  recv1 += status;

  *op = ntohl(*op);
#ifdef DEBUG
  printf ("Recv: Operation is %d\n",*op);
#endif

  if (len > MAXLEN) {
    len = MAXLEN;
  }

  if (len > 0) {
    status = NET_RecvRaw(sock,recbuf,len);
    if (len > buflen) {
      len = buflen;
    }
    memcpy(buffer,recbuf,len);
    if (status < 0) {
      return status;
    }
  }

  recv1 += status;
  return recv1;

}
