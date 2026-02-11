parse_binary(char *buffer, unsigned long size, struct patch *patch)
{


	struct fragment *forward;
	struct fragment *reverse;
	int status;
	int used, used_1;

	forward = parse_binary_hunk(&buffer, &size, &status, &used);
	if (!forward && !status)

		return error("unrecognized binary patch at line %d", linenr-1);
	if (status)

		return status;

	reverse = parse_binary_hunk(&buffer, &size, &status, &used_1);
	if (reverse)
		used += used_1;
	else if (status) {


		free((void*) forward->patch);
		free(forward);
		return status;
	}
	forward->next = reverse;
	patch->fragments = forward;
	patch->is_binary = 1;
	return used;
}
