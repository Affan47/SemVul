DtsFWStopVideo(
    HANDLE  hDevice,
	uint32_t	ChannelId,
	bool	ForceStop
	)
{
	BC_STATUS	sts = BC_STS_SUCCESS;
	DecCmdChannelStopVideo	*sVid;
	DecRspChannelStopVideo	*sVidRsp;

	DTS_LIB_CONTEXT		*Ctx = NULL;
	BC_IOCTL_DATA *pIocData = NULL;

	DTS_GET_CTX(hDevice,Ctx);

	if(!(ForceStop) && (Ctx->State != BC_DEC_STATE_START)
					&& (Ctx->State != BC_DEC_STATE_PAUSE)
					&& (Ctx->State != BC_DEC_STATE_FLUSH))
	{
		DebugLog_Trace(LDIL_DBG,"DtsStopVideo: Channel Not Opened\n");
		return BC_STS_DEC_NOT_STARTED;
	}

	if(!(pIocData = DtsAllocIoctlData(Ctx)))
		return BC_STS_INSUFF_RES;

	sVid = (DecCmdChannelStopVideo *)&pIocData->u.fwCmd.cmd;

	sVid->command		= eCMD_C011_DEC_CHAN_STOP_VIDEO;
	sVid->sequence		= ++Ctx->fwcmdseq;

	sVid->channelId		= ChannelId;
	sVid->pictureRelease= eC011_PIC_REL_INTERNAL;
	sVid->lastPicDisplay= eC011_LASTPIC_DISPLAY_ON;

	if( (sts=DtsDrvCmd(Ctx,BCM_IOC_FW_CMD,1,pIocData,FALSE)) != BC_STS_SUCCESS){
		DebugLog_Trace(LDIL_DBG,"DtsStopVideo: Ioctl failed: %d\n",sts);
		DtsRelIoctlData(Ctx,pIocData);
		return sts;
	}

	sVidRsp = (DecRspChannelStopVideo*)&pIocData->u.fwCmd.rsp;
	if(sVidRsp->status){
		DebugLog_Trace(LDIL_DBG,"DtsStopVideo: StopVideo Failed %d\n",sVidRsp->status);
		DtsRelIoctlData(Ctx,pIocData);
		return BC_STS_FW_CMD_ERR;
	}

	Ctx->State = BC_DEC_STATE_STOP;

	DtsRelIoctlData(Ctx,pIocData);

	return BC_STS_SUCCESS;
}
