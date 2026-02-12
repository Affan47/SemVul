void sc_populate_mount_ns(struct sc_apparmor *apparmor, int snap_update_ns_fd,
			  const char *base_snap_name, const char *snap_name)
{


	char *vanilla_cwd SC_CLEANUP(sc_cleanup_string) = NULL;
	vanilla_cwd = get_current_dir_name();
	if (vanilla_cwd == NULL) {
		die("cannot get the current working directory");
	}

	sc_distro distro = sc_classify_distro();

	if (sc_should_use_normal_mode(distro, base_snap_name)) {

		const struct sc_mount mounts[] = {
			{"/dev"},
			{"/etc"},
			{"/home"},
			{"/root"},
			{"/proc"},
			{"/sys"},
			{"/tmp"},
			{"/var/snap"},
			{"/var/lib/snapd"},
			{"/var/tmp"},
			{"/run"},
			{"/lib/modules",.is_optional = true},
			{"/usr/src"},
			{"/var/log"},
#ifdef MERGED_USR
			{"/run/media", true, "/media"},
#else
			{"/media", true},
#endif
			{"/run/netns", true},


			{"/mnt",.is_optional = true},
			{"/var/lib/extrausers",.is_optional = true},
			{},
		};
		char rootfs_dir[PATH_MAX] = { 0 };
		sc_must_snprintf(rootfs_dir, sizeof rootfs_dir,
				 "%s/%s/current/", SNAP_MOUNT_DIR,
				 base_snap_name);
		if (access(rootfs_dir, F_OK) != 0) {
			if (sc_streq(base_snap_name, "core")) {


				base_snap_name = "ubuntu-core";
				sc_must_snprintf(rootfs_dir, sizeof rootfs_dir,
						 "%s/%s/current/",
						 SNAP_MOUNT_DIR,
						 base_snap_name);
				if (access(rootfs_dir, F_OK) != 0) {
					die("cannot locate the core or legacy core snap (current symlink missing?)");
				}
			}


			if (access(rootfs_dir, F_OK) != 0)
			        die("cannot locate the base snap: %s", base_snap_name);
		}
		struct sc_mount_config normal_config = {
			.rootfs_dir = rootfs_dir,
			.mounts = mounts,
			.distro = distro,
			.normal_mode = true,
			.base_snap_name = base_snap_name,
		};
		sc_bootstrap_mount_namespace(&normal_config);
	} else {


		const struct sc_mount mounts[] = {
			{"/media", true},
			{"/run/netns", true},
			{},
		};
		struct sc_mount_config legacy_config = {
			.rootfs_dir = "/",
			.mounts = mounts,
			.distro = distro,
			.normal_mode = false,
			.base_snap_name = base_snap_name,
		};
		sc_bootstrap_mount_namespace(&legacy_config);
	}


	setup_private_mount(snap_name);


	setup_private_pts();


	sc_call_snap_update_ns(snap_update_ns_fd, snap_name, apparmor);


	if (chdir(vanilla_cwd) != 0) {
		debug("cannot remain in %s, moving to the void directory",
		      vanilla_cwd);
		if (chdir(SC_VOID_DIR) != 0) {
			die("cannot change directory to %s", SC_VOID_DIR);
		}
		debug("successfully moved to %s", SC_VOID_DIR);
	}
}
