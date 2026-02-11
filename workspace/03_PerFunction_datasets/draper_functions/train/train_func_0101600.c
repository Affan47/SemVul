i915_error_state_put(struct i915_error_state_file_priv *error_priv)
{
	if (error_priv->error)
		kref_put(&error_priv->error->ref, i915_error_state_free);
}
