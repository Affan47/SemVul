s5k5baf_fw_get_seq(struct s5k5baf *state, u16 seq_id)
{
	struct s5k5baf_fw *fw = state->fw;
	u16 *data;
	int i;

	if (fw == NULL)
		return NULL;

	data = fw->data + 2 * fw->count;

	for (i = 0; i < fw->count; ++i) {
		if (fw->seq[i].id == seq_id)
			return data + fw->seq[i].offset;
	}

	return NULL;
}
