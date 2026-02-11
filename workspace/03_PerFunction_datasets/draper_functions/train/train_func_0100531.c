vmw_cotable_notify(struct vmw_resource *res, int id)
{
	struct vmw_cotable *vcotbl = vmw_cotable(res);

	if (id < 0 || id >= SVGA_COTABLE_MAX_IDS) {
		DRM_ERROR("Illegal COTable id. Type is %u. Id is %d\n",
			  (unsigned) vcotbl->type, id);
		return -EINVAL;
	}

	if (vcotbl->seen_entries < id) {

		res->id = -1;
		vcotbl->seen_entries = id;
	}

	return 0;
}
