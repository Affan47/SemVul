nvme_trans_supported_vpd_pages(struct nvme_ns *ns,
					struct sg_io_hdr *hdr, u8 *inq_response,
					int alloc_len)
{
	int xfer_len;

	memset(inq_response, 0, STANDARD_INQUIRY_LENGTH);
	inq_response[1] = INQ_SUPPORTED_VPD_PAGES_PAGE;
	inq_response[3] = INQ_NUM_SUPPORTED_VPD_PAGES;
	inq_response[4] = INQ_SUPPORTED_VPD_PAGES_PAGE;
	inq_response[5] = INQ_UNIT_SERIAL_NUMBER_PAGE;
	inq_response[6] = INQ_DEVICE_IDENTIFICATION_PAGE;
	inq_response[7] = INQ_EXTENDED_INQUIRY_DATA_PAGE;
	inq_response[8] = INQ_BDEV_CHARACTERISTICS_PAGE;
	inq_response[9] = INQ_BDEV_LIMITS_PAGE;

	xfer_len = min(alloc_len, STANDARD_INQUIRY_LENGTH);
	return nvme_trans_copy_to_user(hdr, inq_response, xfer_len);
}
