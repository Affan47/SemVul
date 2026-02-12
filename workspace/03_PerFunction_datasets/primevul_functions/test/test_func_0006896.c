smb2_get_next_mid(struct TCP_Server_Info *server)
{
	__u64 mid;

	spin_lock(&GlobalMid_Lock);
	mid = server->CurrentMid++;
	spin_unlock(&GlobalMid_Lock);
	return mid;
}
