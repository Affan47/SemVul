i915_gem_execbuffer_retire_commands(struct drm_device *dev,
				    struct drm_file *file,
				    struct intel_ring_buffer *ring)
{

	ring->gpu_caches_dirty = true;


	(void)i915_add_request(ring, file, NULL);
}
