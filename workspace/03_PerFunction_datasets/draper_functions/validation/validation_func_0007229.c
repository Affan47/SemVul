_send(int sockfd, const struct message* msg)
{
	int n_counter = 0;
	int n_offset = 0;
	do
	{
		n_counter = send(sockfd,
						 ((char*)msg) + n_offset,
						 sizeof(struct message) - n_offset,
						 0);

		if (n_counter > 0)
			n_offset += n_counter;
		else
		{
			PRINT_ERR("send error")
			PRINT_ERR(strerror(errno))
			return FUC_FAILURE;
		}
	} while (n_offset < sizeof(struct message));

	return FUC_SUCCESS;
}
