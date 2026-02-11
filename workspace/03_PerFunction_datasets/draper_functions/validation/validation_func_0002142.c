csio_mb_process_hello_rsp(struct csio_hw *hw, struct csio_mb *mbp,
			  enum fw_retval *retval, enum csio_dev_state *state,
			  uint8_t *mpfn)
{
	struct fw_hello_cmd *rsp = (struct fw_hello_cmd *)(mbp->mb);
	uint32_t value;

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));

	if (*retval == FW_SUCCESS) {
		hw->fwrev = ntohl(rsp->fwrev);

		value = ntohl(rsp->err_to_clearinit);
		*mpfn = FW_HELLO_CMD_MBMASTER_G(value);

		if (value & FW_HELLO_CMD_INIT_F)
			*state = CSIO_DEV_STATE_INIT;
		else if (value & FW_HELLO_CMD_ERR_F)
			*state = CSIO_DEV_STATE_ERR;
		else
			*state = CSIO_DEV_STATE_UNINIT;
	}
}
