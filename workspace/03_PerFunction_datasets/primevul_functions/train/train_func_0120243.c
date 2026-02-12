int check_disk_reg(struct activity *a, int curr, int ref, int pos)
{
	struct stats_disk *sdc, *sdp;
	int j0, j = pos;

	if (!a->nr[ref])


		return -1;

	if (j >= a->nr[ref]) {
		j = a->nr[ref] - 1;
	}
	j0 = j;

	sdc = (struct stats_disk *) ((char *) a->buf[curr] + pos * a->msize);

	do {
		sdp = (struct stats_disk *) ((char *) a->buf[ref] + j * a->msize);

		if ((sdc->major == sdp->major) &&
		    (sdc->minor == sdp->minor)) {


			if ((sdc->nr_ios < sdp->nr_ios) &&
			    (!sdp->rd_sect || (sdc->rd_sect < sdp->rd_sect)) &&
			    (!sdp->wr_sect || (sdc->wr_sect < sdp->wr_sect)) &&
			    (!sdp->dc_sect || (sdc->dc_sect < sdp->dc_sect)))

				return -2;

			return j;
		}
		if (++j >= a->nr[ref]) {
			j = 0;
		}
	}
	while (j != j0);


	return -1;
}
