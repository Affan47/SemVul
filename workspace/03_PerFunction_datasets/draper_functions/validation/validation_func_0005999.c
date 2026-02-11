iscsi_free_discovery_addresses(struct iscsi_discovery_address *addresses)
{
	while (addresses != NULL) {
		struct iscsi_discovery_address *next = addresses->next;

		if (addresses->target_name != NULL) {
			free(discard_const(addresses->target_name));
			addresses->target_name = NULL;
		}
		if (addresses->target_address != NULL) {
			free(discard_const(addresses->target_address));
			addresses->target_address = NULL;
		}
		addresses->next = NULL;
		free(addresses);
		addresses = next;
	}
}
