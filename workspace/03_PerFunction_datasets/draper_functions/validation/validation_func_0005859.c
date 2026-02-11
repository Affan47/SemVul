radeon_dvi_force(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	if (connector->force == DRM_FORCE_ON)
		radeon_connector->use_digital = false;
	if (connector->force == DRM_FORCE_ON_DIGITAL)
		radeon_connector->use_digital = true;
}
