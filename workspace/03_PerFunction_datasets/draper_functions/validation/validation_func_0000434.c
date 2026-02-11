blkid_do_safeprobe(blkid_probe pr)
{
	int i, count = 0, rc = 0;

	if (!pr)
		return -1;

	blkid_probe_start(pr);

	for (i = 0; i < BLKID_NCHAINS; i++) {
		struct blkid_chain *chn;

		chn = pr->cur_chain = &pr->chains[i];
		chn->binary = FALSE;

		DBG(DEBUG_LOWPROBE, printf("chain safeprobe %s %s\n",
				chn->driver->name,
				chn->enabled? "ENABLED" : "DISABLED"));

		if (!chn->enabled)
			continue;

		blkid_probe_chain_reset_position(chn);

		rc = chn->driver->safeprobe(pr, chn);

		blkid_probe_chain_reset_position(chn);


		if (rc < 0)
			goto done;
		if (rc == 0)
			count++;
	}

done:
	blkid_probe_end(pr);
	if (rc < 0)
		return rc;
	return count ? 0 : 1;
}
