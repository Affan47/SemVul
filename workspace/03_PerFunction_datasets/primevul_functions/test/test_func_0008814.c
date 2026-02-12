s64 ntfs_get_attribute_value(const ntfs_volume *vol,
		const ATTR_RECORD *a, u8 *b)
{
	runlist *rl;
	s64 total, r;
	int i;


	if (!vol || !a || !b) {
		errno = EINVAL;
		return 0;
	}


	if (a->type != AT_ATTRIBUTE_LIST && a->flags) {
		ntfs_log_error("Non-zero (%04x) attribute flags. Cannot handle "
			       "this yet.\n", le16_to_cpu(a->flags));
		errno = EOPNOTSUPP;
		return 0;
	}
	if (!a->non_resident) {


		if (le32_to_cpu(a->value_length) + le16_to_cpu(a->value_offset)
				> le32_to_cpu(a->length)) {
			return 0;
		}

		memcpy(b, (const char*)a + le16_to_cpu(a->value_offset),
				le32_to_cpu(a->value_length));
		errno = 0;
		return (s64)le32_to_cpu(a->value_length);
	}


	if (!(a->data_size)) {
		errno = 0;
		return 0;
	}


	rl = ntfs_mapping_pairs_decompress(vol, a, NULL);
	if (!rl) {
		errno = EINVAL;
		return 0;
	}


	for (i = 0, total = 0; rl[i].length; i++) {
		if (total + (rl[i].length << vol->cluster_size_bits) >=
				sle64_to_cpu(a->data_size)) {
			unsigned char *intbuf = NULL;
			s64 intlth;


			intlth = (sle64_to_cpu(a->data_size) - total
					+ vol->cluster_size - 1)
					>> vol->cluster_size_bits;
			if (rl[i].length < intlth)
				intlth = rl[i].length;
			intbuf = (u8*)ntfs_malloc(intlth
						<< vol->cluster_size_bits);
			if (!intbuf) {
				free(rl);
				return 0;
			}


			r = ntfs_pread(vol->dev,
					rl[i].lcn << vol->cluster_size_bits,
					intlth << vol->cluster_size_bits,
					intbuf);
			if (r != intlth << vol->cluster_size_bits) {
#define ESTR "Error reading attribute value"
				if (r == -1)
					ntfs_log_perror(ESTR);
				else if (r < intlth <<
						vol->cluster_size_bits) {
					ntfs_log_debug(ESTR ": Ran out of input data.\n");
					errno = EIO;
				} else {
					ntfs_log_debug(ESTR ": unknown error\n");
					errno = EIO;
				}
#undef ESTR
				free(rl);
				free(intbuf);
				return 0;
			}
			memcpy(b + total, intbuf, sle64_to_cpu(a->data_size) -
					total);
			free(intbuf);
			total = sle64_to_cpu(a->data_size);
			break;
		}


		r = ntfs_pread(vol->dev, rl[i].lcn << vol->cluster_size_bits,
				rl[i].length << vol->cluster_size_bits,
				b + total);
		if (r != rl[i].length << vol->cluster_size_bits) {
#define ESTR "Error reading attribute value"
			if (r == -1)
				ntfs_log_perror(ESTR);
			else if (r < rl[i].length << vol->cluster_size_bits) {
				ntfs_log_debug(ESTR ": Ran out of input data.\n");
				errno = EIO;
			} else {
				ntfs_log_debug(ESTR ": unknown error\n");
				errno = EIO;
			}
#undef ESTR
			free(rl);
			return 0;
		}
		total += r;
	}
	free(rl);
	return total;
}
