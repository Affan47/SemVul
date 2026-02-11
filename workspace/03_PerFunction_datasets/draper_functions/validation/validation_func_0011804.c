io_hdr_unpack(io_hdr_t *hdr, Buf buffer)
{
	safe_unpack16(&hdr->type, buffer);
	safe_unpack16(&hdr->gtaskid, buffer);
	safe_unpack16(&hdr->ltaskid, buffer);
	safe_unpack32(&hdr->length, buffer);
	return SLURM_SUCCESS;

    unpack_error:
	error("io_hdr_unpack error: %m");
	return SLURM_ERROR;
}
