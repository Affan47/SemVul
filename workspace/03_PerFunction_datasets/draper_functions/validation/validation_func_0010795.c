iscsi_create_context(const char *initiator_name)
{
	struct iscsi_context *iscsi;

	iscsi = malloc(sizeof(struct iscsi_context));
	if (iscsi == NULL) {
		printf("Failed to allocate iscsi context\n");
		return NULL;
	}

	bzero(iscsi, sizeof(struct iscsi_context));

	iscsi->initiator_name = strdup(initiator_name);
	if (iscsi->initiator_name == NULL) {
		printf("Failed to allocate initiator name context\n");
		free(iscsi);
		return NULL;
	}

	iscsi->fd = -1;


	srandom(getpid() ^ time(NULL));
	iscsi_set_random_isid(iscsi);

	return iscsi;
}
