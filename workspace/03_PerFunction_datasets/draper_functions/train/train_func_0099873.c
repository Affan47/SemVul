ODF_CanHandleStream(GF_BaseDecoder *ifce, u32 StreamType, GF_ESD *esd, u8 PL)
{
	ODPriv *priv = (ODPriv *)ifce->privateStack;
	if (StreamType==GF_STREAM_OD) {
		priv->PL = PL;
		return GF_CODEC_SUPPORTED;
	}
	return GF_CODEC_NOT_SUPPORTED;
}
