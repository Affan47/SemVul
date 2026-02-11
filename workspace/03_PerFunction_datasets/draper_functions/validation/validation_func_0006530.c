sig_chld(int ) {
  int old_errno = errno;
  int status;
  for(;;) {
    int id=waitpid(-1,&status,WNOHANG);
    if((id == 0) || (id == -1)) break;
    curr_connections--;
    if(curr_connections < -10) curr_connections=-10;
  };
  errno = old_errno;
}
