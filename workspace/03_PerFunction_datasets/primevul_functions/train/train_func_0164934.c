static int sctp_auth_compare_vectors(struct sctp_auth_bytes *vector1,
			      struct sctp_auth_bytes *vector2)
{
	int diff;
	int i;
	const __u8 *longer;

	diff = vector1->len - vector2->len;
	if (diff) {
		longer = (diff > 0) ? vector1->data : vector2->data;


		for (i = 0; i < abs(diff); i++ ) {
			if (longer[i] != 0)
				return diff;
		}
	}


	return memcmp(vector1->data, vector2->data, vector1->len);
}
