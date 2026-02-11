qla25xx_delete_rsp_que(struct scsi_qla_host *vha, struct rsp_que *rsp)
{
	int ret = -1;

	if (rsp) {
		rsp->options |= BIT_0;
		ret = qla25xx_init_rsp_que(vha, rsp);
	}
	if (ret == QLA_SUCCESS)
		qla25xx_free_rsp_que(vha, rsp);

	return ret;
}
