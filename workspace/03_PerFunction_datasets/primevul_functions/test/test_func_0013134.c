struct sctp_chunk *sctp_make_datafrag_empty(const struct sctp_association *asoc,
					    const struct sctp_sndrcvinfo *sinfo,
					    int len, __u8 flags, gfp_t gfp)
{
	struct sctp_chunk *retval;
	struct sctp_datahdr dp;


	memset(&dp, 0, sizeof(dp));
	dp.ppid = sinfo->sinfo_ppid;
	dp.stream = htons(sinfo->sinfo_stream);


	if (sinfo->sinfo_flags & SCTP_UNORDERED)
		flags |= SCTP_DATA_UNORDERED;

	retval = sctp_make_data(asoc, flags, sizeof(dp) + len, gfp);
	if (!retval)
		return NULL;

	retval->subh.data_hdr = sctp_addto_chunk(retval, sizeof(dp), &dp);
	memcpy(&retval->sinfo, sinfo, sizeof(struct sctp_sndrcvinfo));

	return retval;
}
