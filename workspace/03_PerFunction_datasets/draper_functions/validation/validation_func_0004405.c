execute_cdb_mode_sense_6 (struct ndm_session *sess,
  ndmp9_execute_cdb_request *request,
  ndmp9_execute_cdb_reply *reply)
{
	unsigned char *cdb = (unsigned char *)request->cdb.cdb_val;
	int page, subpage;
	char *response;
	int response_len;
	char *p;

	if (request->cdb.cdb_len != 6
	    || request->data_dir != NDMP9_SCSI_DATA_DIR_IN)
		return scsi_fail_with_sense_code(sess, reply,
		    SCSI_STATUS_CHECK_CONDITION,
		    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
		    ASQ_INVALID_FIELD_IN_CDB);
	page = cdb[2] & 0x3f;
	subpage = cdb[3];

	switch ((page << 8) + subpage) {
	case 0x1D00:
		if (request->datain_len < 20 || cdb[4] < 20)
			return scsi_fail_with_sense_code(sess, reply,
			    SCSI_STATUS_CHECK_CONDITION,
			    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
			    ASQ_INVALID_FIELD_IN_CDB);

		response_len = 24;
		p = response = NDMOS_API_MALLOC(response_len);
		NDMOS_API_BZERO(response, response_len);
		*(p++) = response_len;
		*(p++) = 0;
		*(p++) = 0;
		*(p++) = 0;
		*(p++) = 0x1D;
		*(p++) = 18;
		*(p++) = (MTE_FIRST >> 8) & 0xff;
		*(p++) = MTE_FIRST & 0xff;
		*(p++) = (MTE_COUNT >> 8) & 0xff;
		*(p++) = MTE_COUNT & 0xff;
		*(p++) = (STORAGE_FIRST >> 8) & 0xff;
		*(p++) = STORAGE_FIRST & 0xff;
		*(p++) = (STORAGE_COUNT >> 8) & 0xff;
		*(p++) = STORAGE_COUNT & 0xff;
		*(p++) = (IE_FIRST >> 8) & 0xff;
		*(p++) = IE_FIRST & 0xff;
		*(p++) = (IE_COUNT >> 8) & 0xff;
		*(p++) = IE_COUNT & 0xff;
		*(p++) = (DTE_FIRST >> 8) & 0xff;
		*(p++) = DTE_FIRST & 0xff;
		*(p++) = (DTE_COUNT >> 8) & 0xff;
		*(p++) = DTE_COUNT & 0xff;

		break;

	default:
		return scsi_fail_with_sense_code(sess, reply,
		    SCSI_STATUS_CHECK_CONDITION,
		    SCSI_SENSE_KEY_ILLEGAL_REQUEST,
		    ASQ_INVALID_FIELD_IN_CDB);
	}

	reply->datain.datain_len = response_len;
	reply->datain.datain_val = response;

	return NDMP9_NO_ERR;
}
