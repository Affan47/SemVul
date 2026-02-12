static void rfx_update_context_properties(RFX_CONTEXT* context)
{
	UINT16 properties;

	properties = 1;
	properties |= (context->flags << 1);
	properties |= (COL_CONV_ICT << 4);
	properties |= (CLW_XFORM_DWT_53_A << 6);
	properties |= ((context->mode == RLGR1 ? CLW_ENTROPY_RLGR1 : CLW_ENTROPY_RLGR3) << 10);
	properties |= (SCALAR_QUANTIZATION << 14);
	context->properties = properties;
}
