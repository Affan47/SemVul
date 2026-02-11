print_port(serv_response *res) {
  if (res->status == OK && res->port != 0)
    printf("%s %d %s %s\n",
	   res->ip,
	   res->port,
	   PROTYPE2STR(res->protocol),
	   S_PORTSTATE[res->state]);
  else
    printf("%s\n", S_REPLY[res->status]);
}
