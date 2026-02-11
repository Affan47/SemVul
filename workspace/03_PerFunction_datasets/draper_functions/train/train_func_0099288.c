pk_backend_get_requires (PkBackend *backend,
			 PkBackendJob *job,
			 PkBitfield filters,
			 gchar **package_ids,
			 gboolean recursive)
{
	g_return_if_fail (PK_IS_BACKEND (backend));
	g_return_if_fail (backend->priv->desc->get_requires != NULL);


	g_assert (pk_backend_job_get_vfunc_enabled (job, PK_BACKEND_SIGNAL_FINISHED));

	pk_backend_job_set_role (job, PK_ROLE_ENUM_GET_REQUIRES);
	pk_backend_job_set_parameters (job, g_variant_new ("(t^asb)",
							   filters,
							   package_ids,
							   recursive));
	backend->priv->desc->get_requires (backend, job, filters, package_ids, recursive);
}
