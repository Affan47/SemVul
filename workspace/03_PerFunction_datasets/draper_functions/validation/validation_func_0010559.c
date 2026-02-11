mpt_put_msg_frame(u8 cb_idx, MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf)
{
	u32 mf_dma_addr;
	int req_offset;
	u16	 req_idx;


	mf->u.frame.hwhdr.msgctxu.fld.cb_idx = cb_idx;
	req_offset = (u8 *)mf - (u8 *)ioc->req_frames;

	req_idx = req_offset / ioc->req_sz;
	mf->u.frame.hwhdr.msgctxu.fld.req_idx = cpu_to_le16(req_idx);
	mf->u.frame.hwhdr.msgctxu.fld.rsvd = 0;

	DBG_DUMP_PUT_MSG_FRAME(ioc, (u32 *)mf);

	mf_dma_addr = (ioc->req_frames_low_dma + req_offset) | ioc->RequestNB[req_idx];
	dsgprintk(ioc, printk(MYIOC_s_DEBUG_FMT "mf_dma_addr=%x req_idx=%d "
	    "RequestNB=%x\n", ioc->name, mf_dma_addr, req_idx,
	    ioc->RequestNB[req_idx]));
	CHIPREG_WRITE32(&ioc->chip->RequestFifo, mf_dma_addr);
}
