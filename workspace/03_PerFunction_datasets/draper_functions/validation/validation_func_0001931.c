rebootpwr_run_state(struct fpi_ssm *ssm)
{
	struct fp_img_dev *dev = ssm->priv;
	struct uru4k_dev *urudev = dev->priv;

	switch (ssm->cur_state) {
	case REBOOTPWR_SET_HWSTAT:
		urudev->rebootpwr_ctr = 100;
		sm_set_hwstat(ssm, urudev->last_hwstat & 0xf);
		break;
	case REBOOTPWR_GET_HWSTAT:
		sm_read_reg(ssm, REG_HWSTAT);
		break;
	case REBOOTPWR_CHECK_HWSTAT:
		urudev->last_hwstat = urudev->last_reg_rd[0];
		if (urudev->last_hwstat & 0x1)
			fpi_ssm_mark_completed(ssm);
		else
			fpi_ssm_next_state(ssm);
		break;
	case REBOOTPWR_PAUSE:
		if (fpi_timeout_add(10, rebootpwr_pause_cb, ssm) == NULL)
			fpi_ssm_mark_aborted(ssm, -ETIME);
		break;
	}
}
