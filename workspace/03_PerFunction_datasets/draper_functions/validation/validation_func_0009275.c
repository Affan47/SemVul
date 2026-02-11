print_ace(struct cifs_ace *pace, char *end_of_acl, int raw)
{
	uint16_t size;


	if (end_of_acl < (char *)pace + offsetof(struct cifs_ace, size) + 1)
		return;

	size = le16toh(pace->size);


	if (size < 16)
		return;


	if (end_of_acl < (char *)pace + size)
		return;

	printf("ACL:");
	print_sid((struct cifs_sid *)&pace->sid, raw);
	printf(":");
	print_ace_type(pace->type, raw);
	printf("/");
	print_ace_flags(pace->flags, raw);
	printf("/");
	print_ace_mask(le32toh(pace->access_req), raw);

	return;
}
