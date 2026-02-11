iscsi_write10_async(struct iscsi_context *iscsi, int lun, iscsi_command_cb cb, unsigned char *data, int datalen, int lba, int fua, int fuanv, int blocksize, void *private_data)
{
	struct scsi_task *task;
	struct iscsi_data outdata;
	int ret;

	if (datalen % blocksize != 0) {
		printf("datalen:%d is not a multiple of the blocksize:%d\n", datalen, blocksize);
		return -1;
	}

	if ((task = scsi_cdb_write10(lba, datalen, fua, fuanv, blocksize)) == NULL) {
		printf("Failed to create read10 cdb\n");
		return -2;
	}

	outdata.data = data;
	outdata.size = datalen;

	ret = iscsi_scsi_command_async(iscsi, lun, task, cb, &outdata, private_data);

	return ret;
}
