static int parse_dos_extended(blkid_probe pr, blkid_parttable tab,
		uint32_t ex_start, uint32_t ex_size, int ssf)
{
	blkid_partlist ls = blkid_probe_get_partlist(pr);
	uint32_t cur_start = ex_start, cur_size = ex_size;
	unsigned char *data;
	int ct_nodata = 0;
	int i;

	DBG(LOWPROBE, ul_debug("parse EBR [start=%d, size=%d]", ex_start/ssf, ex_size/ssf));
	if (ex_start == 0) {
		DBG(LOWPROBE, ul_debug("Bad offset in primary extended partition -- ignore"));
		return 0;
	}

	while (1) {
		struct dos_partition *p, *p0;
		uint32_t start, size;

		if (++ct_nodata > 100)
			return BLKID_PROBE_OK;
		data = blkid_probe_get_sector(pr, cur_start);
		if (!data) {
			if (errno)
				return -errno;
			goto leave;
		}

		if (!mbr_is_valid_magic(data))
			goto leave;

		p0 = mbr_get_partition(data, 0);


		for (p = p0, i = 0; i < 4; i++, p++) {
			uint32_t abs_start;
			blkid_partition par;


			start = dos_partition_get_start(p) * ssf;
			size = dos_partition_get_size(p) * ssf;
			abs_start = cur_start + start;

			if (!size || is_extended(p))
				continue;
			if (i >= 2) {


				if (start + size > cur_size)
					continue;
				if (abs_start < ex_start)
					continue;
				if (abs_start + size > ex_start + ex_size)
					continue;
			}


			if (blkid_partlist_get_partition_by_start(ls, abs_start)) {
				DBG(LOWPROBE, ul_debug("#%d: EBR duplicate data partition [abs start=%u] -- ignore",
							i + 1, abs_start));
				continue;
			}

			par = blkid_partlist_add_partition(ls, tab, abs_start, size);
			if (!par)
				return -ENOMEM;

			blkid_partition_set_type(par, p->sys_ind);
			blkid_partition_set_flags(par, p->boot_ind);
			blkid_partition_gen_uuid(par);
			ct_nodata = 0;
		}


		for (p = p0, i = 0; i < 4; i++, p++) {
			start = dos_partition_get_start(p) * ssf;
			size = dos_partition_get_size(p) * ssf;

			if (size && is_extended(p)) {
				if (start == 0)
					DBG(LOWPROBE, ul_debug("#%d: EBR link offset is zero -- ignore", i + 1));
				else
					break;
			}
		}
		if (i == 4)
			goto leave;

		cur_start = ex_start + start;
		cur_size = size;
	}
leave:
	return BLKID_PROBE_OK;
}
