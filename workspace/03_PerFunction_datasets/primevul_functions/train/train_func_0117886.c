umount_file (char *arg) {
	struct mntentchn *mc, *fs;
	const char *file, *options;
	int fstab_has_user, fstab_has_users, fstab_has_owner, fstab_has_group;
	int ok;
	struct stat statbuf;

	if (!*arg) {
		die(2, _("Cannot unmount \"\"\n"));
		return 0;
	}

	file = canonicalize(arg);


	if (!stat(file, &statbuf) && S_ISREG(statbuf.st_mode)) {
		char *loopdev = NULL;
		switch (find_loopdev_by_backing_file(file, &loopdev)) {
		case 0:
			if (verbose)
				printf(_("%s is associated with %s, trying to unmount it\n"),
				       arg, loopdev);
			file = loopdev;
			break;
		case 2:
			if (verbose)
				printf(_("%s is associated with more than one loop device: not unmounting\n"),
				       arg);
			break;
		}
	}

	if (verbose > 1)
		printf(_("Trying to unmount %s\n"), file);

	mc = getmntdirbackward(file, NULL);
	if (!mc) {
		mc = getmntdevbackward(file, NULL);
		if (mc) {
			struct mntentchn *mc1;
			char *cn;

			mc1 = getmntdirbackward(mc->m.mnt_dir, NULL);
			if (!mc1)


				die(EX_SOFTWARE,
				    _("umount: confused when analyzing mtab"));

			cn = canonicalize(mc1->m.mnt_fsname);
			if (cn && strcmp(file, cn)) {


				die(EX_FAIL, _("umount: cannot unmount %s -- %s is "
				    "mounted over it on the same point"),
				    file, mc1->m.mnt_fsname);
			}
			free(cn);
		}
	}
	if (!mc && verbose)
		printf(_("Could not find %s in mtab\n"), file);

	if (restricted) {
		char *mtab_user = NULL;

		if (!mc)
			die(2,
			    _("umount: %s is not mounted (according to mtab)"),
			    file);


		if (external_allowed) {
			char *uhelper = NULL;

			if (mc->m.mnt_opts)
				uhelper = get_option_value(mc->m.mnt_opts,
							   "uhelper=");
			if (uhelper) {
				int status = 0;
				if (check_special_umountprog(arg, arg,
							uhelper, &status))
					return status;
			}
		}


		if (!is_mounted_once(file) && strcmp(mc->m.mnt_type,"nfs"))
			die(2,
			    _("umount: it seems %s is mounted multiple times"),
			    file);


		fs = getfs_by_devdir(mc->m.mnt_fsname, mc->m.mnt_dir);
		if (!fs) {
			fs = getfs_by_dir(file);
			if (!fs && !getfs_by_spec(file))
				die (2,
				     _("umount: %s is not in the fstab "
				       "(and you are not root)"),
				     file);


			if (!fs || !is_valid_loop(mc, fs))
				die (2, _("umount: %s mount disagrees with "
					  "the fstab"), file);
		}


		options = fs->m.mnt_opts;
		if (!options)
			options = "";
		fstab_has_user = contains(options, "user");
		fstab_has_users = contains(options, "users");
		fstab_has_owner = contains(options, "owner");
		fstab_has_group = contains(options, "group");
		ok = 0;

		if (fstab_has_users)
			ok = 1;

		if (!ok && (fstab_has_user || fstab_has_owner ||
			    fstab_has_group)) {
			char *user = getusername();

			options = mc->m.mnt_opts;
			if (!options)
				options = "";
			mtab_user = get_option_value(options, "user=");

			if (user && mtab_user && streq (user, mtab_user))
				ok = 1;
		}
		if (!ok)
			die (2, _("umount: only %s can unmount %s from %s"),
			     mtab_user ? mtab_user : "root",
			     fs->m.mnt_fsname, fs->m.mnt_dir);
	}

	if (mc)
		return umount_one_bw (file, mc);
	else
		return umount_one (arg, arg, arg, arg, NULL);
}
