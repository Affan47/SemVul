pk_backend_get_updates_timeout (gpointer data)
{
	PkBackendJob *job = (PkBackendJob *) data;
	PkBackendDummyJobData *job_data = pk_backend_job_get_user_data (job);

	if (priv->use_blocked) {
		if (!priv->updated_powertop && !priv->updated_kernel && !priv->updated_gtkhtml) {
			pk_backend_job_package (job, PK_INFO_ENUM_BLOCKED,
						"vino;2.24.2.fc9;i386;fedora",
						"Remote desktop server for the desktop");
		}
	}
	if (!priv->updated_powertop) {
		pk_backend_job_package (job, PK_INFO_ENUM_NORMAL,
					"powertop;1.8-1.fc8;i386;fedora",
					"Power consumption monitor");
	}
	if (!priv->updated_kernel) {
		pk_backend_job_package (job, PK_INFO_ENUM_BUGFIX,
					"kernel;2.6.23-0.115.rc3.git1.fc8;i386;installed",
					"The Linux kernel (the core of the Linux operating system)");
	}
	if (!priv->updated_gtkhtml) {
		pk_backend_job_package (job, PK_INFO_ENUM_SECURITY,
					"gtkhtml2;2.19.1-4.fc8;i386;fedora",
					"An HTML widget for GTK+ 2.0");
	}
	pk_backend_job_finished (job);
	job_data->signal_timeout = 0;
	return FALSE;
}
