blkid_probe_verify_csum(blkid_probe pr, uint64_t csum, uint64_t expected)
{
	if (csum != expected) {
		struct blkid_chain *chn = blkid_probe_get_chain(pr);

		DBG(LOWPROBE, ul_debug(
				"incorrect checksum for type %s,"
				" got %jX, expected %jX",
				blkid_probe_get_probername(pr),
				csum, expected));


		if (chn->driver->id == BLKID_CHAIN_SUBLKS
		    && (chn->flags & BLKID_SUBLKS_BADCSUM)) {
			blkid_probe_set_value(pr, "SBBADCSUM", (unsigned char *) "1", 2);
			goto accept;
		}
		return 0;
	}

accept:
	return 1;
}
