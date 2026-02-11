agent_close(struct ssh_agent_struct *agent) {
  if (agent == NULL) {
    return;
  }

  if (getenv("SSH_AUTH_SOCK")) {
    ssh_socket_close(agent->sock);
  }
}
