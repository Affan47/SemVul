intel_connector_atomic_get_property(struct drm_connector *connector,
				    const struct drm_connector_state *state,
				    struct drm_property *property,
				    uint64_t *val)
{
	int i;


	for (i = 0; i < connector->base.properties->count; i++) {
		if (connector->base.properties->properties[i] == property) {
			*val = connector->base.properties->values[i];
			return 0;
		}
	}

	return -EINVAL;
}
