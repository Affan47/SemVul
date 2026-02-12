ssh_kill_proxy_command(void)
{


	if (proxy_command_pid > 1)
		kill(proxy_command_pid, SIGHUP);
}
