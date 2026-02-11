bfa_cb_ioim_done(void *drv, struct bfad_ioim_s *dio,
			enum bfi_ioim_status io_status, u8 scsi_status,
			int sns_len, u8 *sns_info, s32 residue)
{
	struct scsi_cmnd *cmnd = (struct scsi_cmnd *)dio;
	struct bfad_s         *bfad = drv;
	struct bfad_itnim_data_s *itnim_data;
	struct bfad_itnim_s *itnim;
	u8         host_status = DID_OK;

	switch (io_status) {
	case BFI_IOIM_STS_OK:
		bfa_trc(bfad, scsi_status);
		scsi_set_resid(cmnd, 0);

		if (sns_len > 0) {
			bfa_trc(bfad, sns_len);
			if (sns_len > SCSI_SENSE_BUFFERSIZE)
				sns_len = SCSI_SENSE_BUFFERSIZE;
			memcpy(cmnd->sense_buffer, sns_info, sns_len);
		}

		if (residue > 0) {
			bfa_trc(bfad, residue);
			scsi_set_resid(cmnd, residue);
			if (!sns_len && (scsi_status == SAM_STAT_GOOD) &&
				(scsi_bufflen(cmnd) - residue) <
					cmnd->underflow) {
				bfa_trc(bfad, 0);
				host_status = DID_ERROR;
			}
		}
		cmnd->result = ScsiResult(host_status, scsi_status);

		break;

	case BFI_IOIM_STS_TIMEDOUT:
		host_status = DID_TIME_OUT;
		cmnd->result = ScsiResult(host_status, 0);
		break;
	case BFI_IOIM_STS_PATHTOV:
		host_status = DID_TRANSPORT_DISRUPTED;
		cmnd->result = ScsiResult(host_status, 0);
		break;
	default:
		host_status = DID_ERROR;
		cmnd->result = ScsiResult(host_status, 0);
	}


	if (cmnd->device->host != NULL)
		scsi_dma_unmap(cmnd);

	cmnd->host_scribble = NULL;
	bfa_trc(bfad, cmnd->result);

	itnim_data = cmnd->device->hostdata;
	if (itnim_data) {
		itnim = itnim_data->itnim;
		if (!cmnd->result && itnim &&
			 (bfa_lun_queue_depth > cmnd->device->queue_depth)) {

			bfad_ramp_up_qdepth(itnim, cmnd->device);
		} else if (cmnd->result == SAM_STAT_TASK_SET_FULL && itnim) {

			bfad_handle_qfull(itnim, cmnd->device);
		}
	}

	cmnd->scsi_done(cmnd);
}
