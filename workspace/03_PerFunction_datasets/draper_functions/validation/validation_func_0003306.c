liblo10k1lf_find_part_il(FILE *file, unsigned int part_type, unsigned int part_id, unsigned int part_length, int il, liblo10k1_file_part_t *part)
{
	int err;
	while (1) {
		if (fread(part, sizeof(liblo10k1_file_part_t), 1, file) != 1)
			return LD10K1_LF_ERR_READ;


		if (part->part_type == part_type && part->part_id == part_id) {
			if (part->part_type == LD10K1_FP_TYPE_NORMAL) {
				if (il || part->part_length == part_length)
					return 0;
				else
					return LD10K1_LF_ERR_PART_SIZE;
			} else {
				if (part->part_length != 0)
					return LD10K1_LF_ERR_PART_SIZE;
				else
					return 0;
			}
		} else {
			if ((err = liblo10k1lf_skip_part(file, part)) < 0)
				return err;
		}
	}
}
