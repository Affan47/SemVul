vmw_cmd_dx_cid_check(struct vmw_private *dev_priv,
				struct vmw_sw_context *sw_context,
				SVGA3dCmdHeader *header)
{
	struct vmw_resource_val_node *ctx_node = sw_context->dx_ctx_node;

	if (unlikely(ctx_node == NULL)) {
		DRM_ERROR("DX Context not set.\n");
		return -EINVAL;
	}

	return 0;
}
