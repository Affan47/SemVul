static void sc_bootstrap_mount_namespace(const struct sc_mount_config *config)
{
	char scratch_dir[] = "/tmp/snap.rootfs_XXXXXX";
	char src[PATH_MAX] = { 0 };
	char dst[PATH_MAX] = { 0 };
	if (mkdtemp(scratch_dir) == NULL) {
		die("cannot create temporary directory for the root file system");
	}


	debug("scratch directory for constructing namespace: %s", scratch_dir);


	sc_do_mount("none", "/", NULL, MS_REC | MS_SHARED, NULL);


	sc_do_mount(scratch_dir, scratch_dir, NULL, MS_BIND, NULL);


	sc_do_mount("none", scratch_dir, NULL, MS_UNBINDABLE, NULL);


	sc_do_mount(config->rootfs_dir, scratch_dir, NULL, MS_REC | MS_BIND,
		    NULL);


	sc_do_mount("none", scratch_dir, NULL, MS_REC | MS_SLAVE, NULL);


	for (const struct sc_mount * mnt = config->mounts; mnt->path != NULL;
	     mnt++) {
		if (mnt->is_bidirectional && mkdir(mnt->path, 0755) < 0 &&
		    errno != EEXIST) {
			die("cannot create %s", mnt->path);
		}
		sc_must_snprintf(dst, sizeof dst, "%s/%s", scratch_dir,
				 mnt->path);
		if (mnt->is_optional) {
			bool ok = sc_do_optional_mount(mnt->path, dst, NULL,
						       MS_REC | MS_BIND, NULL);
			if (!ok) {

				continue;
			}
		} else {
			sc_do_mount(mnt->path, dst, NULL, MS_REC | MS_BIND,
				    NULL);
		}
		if (!mnt->is_bidirectional) {


			sc_do_mount("none", dst, NULL, MS_REC | MS_SLAVE, NULL);
		}
		if (mnt->altpath == NULL) {
			continue;
		}


		sc_must_snprintf(dst, sizeof dst, "%s/%s", scratch_dir,
				 mnt->altpath);
		struct stat stat_buf;
		if (lstat(dst, &stat_buf) < 0) {
			die("cannot lstat %s", dst);
		}
		if ((stat_buf.st_mode & S_IFMT) == S_IFLNK) {
			die("cannot bind mount alternate path over a symlink: %s", dst);
		}
		sc_do_mount(mnt->path, dst, NULL, MS_REC | MS_BIND, NULL);
		if (!mnt->is_bidirectional) {
			sc_do_mount("none", dst, NULL, MS_REC | MS_SLAVE, NULL);
		}
	}
	if (config->normal_mode) {


		const char *dirs_from_core[] =
		    { "/etc/alternatives", "/etc/ssl", "/etc/nsswitch.conf",
			NULL
		};
		for (const char **dirs = dirs_from_core; *dirs != NULL; dirs++) {
			const char *dir = *dirs;
			struct stat buf;
			if (access(dir, F_OK) == 0) {
				sc_must_snprintf(src, sizeof src, "%s%s",
						 config->rootfs_dir, dir);
				sc_must_snprintf(dst, sizeof dst, "%s%s",
						 scratch_dir, dir);
				if (lstat(src, &buf) == 0
				    && lstat(dst, &buf) == 0) {
					sc_do_mount(src, dst, NULL, MS_BIND,
						    NULL);
					sc_do_mount("none", dst, NULL, MS_SLAVE,
						    NULL);
				}
			}
		}
	}


	if (config->distro == SC_DISTRO_CORE_OTHER
	    || !sc_streq(config->base_snap_name, "core")) {


		sc_must_snprintf(dst, sizeof dst, "%s/usr/lib/snapd",
				 scratch_dir);


		char *src = NULL;
		char self[PATH_MAX + 1] = { 0 };
		if (readlink("/proc/self/exe", self, sizeof(self) - 1) < 0) {
			die("cannot read /proc/self/exe");
		}

		if (strstr(self, "/snap-confine") == NULL) {
			die("cannot use result from readlink: %s", self);
		}
		src = dirname(self);


		if (src[0] != '/') {
			die("cannot use the result of dirname(): %s", src);
		}

		sc_do_mount(src, dst, NULL, MS_BIND | MS_RDONLY, NULL);
		sc_do_mount("none", dst, NULL, MS_SLAVE, NULL);
	}


	sc_must_snprintf(dst, sizeof dst, "%s/snap", scratch_dir);
	sc_do_mount(SNAP_MOUNT_DIR, dst, NULL, MS_BIND | MS_REC | MS_SLAVE,
		    NULL);
	sc_do_mount("none", dst, NULL, MS_REC | MS_SLAVE, NULL);


	if (access(SC_HOSTFS_DIR, F_OK) != 0) {
		debug("creating missing hostfs directory");
		if (mkdir(SC_HOSTFS_DIR, 0755) != 0) {
			die("cannot perform operation: mkdir %s",
			    SC_HOSTFS_DIR);
		}
	}


	struct stat sb;
	if (stat(SC_HOSTFS_DIR, &sb) < 0) {
		die("cannot stat %s", SC_HOSTFS_DIR);
	}
	if (sb.st_uid != 0 || sb.st_gid != 0) {
		if (chown(SC_HOSTFS_DIR, 0, 0) < 0) {
			die("cannot change user/group owner of %s to root",
			    SC_HOSTFS_DIR);
		}
	}


	sc_must_snprintf(dst, sizeof dst, "%s/%s", scratch_dir, SC_HOSTFS_DIR);
	sc_do_mount(dst, dst, NULL, MS_BIND, NULL);
	sc_do_mount("none", dst, NULL, MS_PRIVATE, NULL);


	if (config->distro == SC_DISTRO_CLASSIC) {
		sc_mount_nvidia_driver(scratch_dir);
	}


	debug("performing operation: pivot_root %s %s", scratch_dir, dst);
	if (syscall(SYS_pivot_root, scratch_dir, dst) < 0) {
		die("cannot perform operation: pivot_root %s %s", scratch_dir,
		    dst);
	}


	sc_must_snprintf(dst, sizeof dst, "%s/%s", SC_HOSTFS_DIR, scratch_dir);
	sc_do_umount(dst, 0);


	debug("performing operation: rmdir %s", dst);
	if (rmdir(scratch_dir) < 0) {
		die("cannot perform operation: rmdir %s", dst);
	};


	sc_do_mount("none", SC_HOSTFS_DIR, NULL, MS_REC | MS_SLAVE, NULL);


	sc_must_snprintf(src, sizeof src, "%s/sys", SC_HOSTFS_DIR);
	sc_do_umount(src, UMOUNT_NOFOLLOW | MNT_DETACH);


	sc_must_snprintf(src, sizeof src, "%s/dev", SC_HOSTFS_DIR);
	sc_do_umount(src, UMOUNT_NOFOLLOW | MNT_DETACH);


	sc_must_snprintf(src, sizeof src, "%s/proc", SC_HOSTFS_DIR);
	sc_do_umount(src, UMOUNT_NOFOLLOW | MNT_DETACH);
}
