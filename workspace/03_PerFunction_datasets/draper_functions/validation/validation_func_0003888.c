translate_uidgid_to_server(struct afp_volume * volume,
	unsigned int * newuid, unsigned int *newgid)
{
	switch(volume->mapping) {
		case AFP_MAPPING_COMMON:


		break;
		case AFP_MAPPING_LOGINIDS:


			*newuid=volume->server->server_uid;
			*newgid=volume->server->server_gid;
			break;
		default:
		case AFP_MAPPING_UNKNOWN:
			return -1;
		break;
	}
	return 0;
}
