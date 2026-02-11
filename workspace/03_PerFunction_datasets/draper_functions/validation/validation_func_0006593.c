fm10k_mbx_verify_remote_crc(struct fm10k_mbx_info *mbx)
{
	struct fm10k_mbx_fifo *fifo = &mbx->rx;
	u16 len = mbx->head_len;
	u16 offset = fm10k_fifo_tail_offset(fifo, mbx->pushed) - len;
	u16 crc;


	if (len)
		mbx->remote = fm10k_fifo_crc(fifo, offset, len, mbx->remote);


	crc = fm10k_crc_16b(&mbx->mbx_hdr, mbx->remote, 1);


	return crc ? FM10K_MBX_ERR_CRC : 0;
}
