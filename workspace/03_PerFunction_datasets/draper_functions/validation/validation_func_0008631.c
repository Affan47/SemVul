guc_client_free(struct drm_device *dev,
			    struct i915_guc_client *client)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_guc *guc = &dev_priv->guc;

	if (!client)
		return;

	if (client->doorbell_id != GUC_INVALID_DOORBELL_ID) {


		guc_disable_doorbell(guc, client);
		host2guc_release_doorbell(guc, client);
		release_doorbell(guc, client->doorbell_id);
	}


	gem_release_guc_obj(client->client_obj);

	if (client->ctx_index != GUC_INVALID_CTX_ID) {
		guc_fini_ctx_desc(guc, client);
		ida_simple_remove(&guc->ctx_ids, client->ctx_index);
	}

	kfree(client);
}
