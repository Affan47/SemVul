extract_ssh_port(char * server, char * server_name)
{
  int sctr=0, ctr=0, i, ssh_port = 22;
  char str[STRING_BLOCK];


  for (i = 0; i < strlen(server); i++) {
    if ((server[i] == ':') && (i < strlen(server)-1)) {
      if (server[i+1] != '/') {
        server_name[sctr++] = server[i];
        i++;
        while (i < strlen(server)-1) {
          if (server[i] == '/') {
            str[ctr++] = 0;
            break;
          }
          str[ctr++] = server[i];
          i++;
        }
      }
    }
    server_name[sctr++] = server[i];
  }
  server_name[sctr++] = 0;
  if (ctr > 0) {
    ssh_port = atoi(str);
  }

  return ssh_port;
}
