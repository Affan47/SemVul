umount_one (const char *spec, const char *node, const char *type,
	    const char *opts, struct mntentchn *mc) {
	int umnt_err = 0;
	int isroot;
	int res = 0;
	int status;
	int extra_flags = 0;
	const char *loopdev, *target = node;
	char *targetbuf = NULL;
	int myloop = 0;


	isroot = (streq (node, "/") || streq (node, "root")
		  || streq (node, "rootfs"));
	if (isroot)
		nomtab++;


	if (check_special_umountprog(spec, node, type, &status))
		return status;


	if (fake)
		goto writemtab;


	if (delloop && is_loop_device(spec))
		myloop = 1;

	if (restricted) {
		if (umount_nofollow_support())
			extra_flags |= UMOUNT_NOFOLLOW;


		target = chdir_to_parent(node, &targetbuf);
	}

	if (lazy) {
		res = umount2 (target, MNT_DETACH | extra_flags);
		if (res < 0)
			umnt_err = errno;
		goto writemtab;
	}

	if (force) {
		res = umount2 (target, MNT_FORCE | extra_flags);
		if (res == -1) {
			int errsv = errno;
			perror("umount2");
			errno = errsv;
			if (errno == ENOSYS) {
				if (verbose)
					printf(_("no umount2, trying umount...\n"));
				res = umount (target);
			}
		}
	} else if (extra_flags)
		res = umount2 (target, extra_flags);
	else
		res = umount (target);

	free(targetbuf);

	if (res < 0)
		umnt_err = errno;

	if (res < 0 && remount && umnt_err == EBUSY) {

		res = mount(spec, node, NULL,
			    MS_MGC_VAL | MS_REMOUNT | MS_RDONLY, NULL);
		if (res == 0) {
			fprintf(stderr,
				_("umount: %s busy - remounted read-only\n"),
				spec);
			if (mc && !nomtab) {

				struct my_mntent remnt;
				remnt.mnt_fsname = mc->m.mnt_fsname;
				remnt.mnt_dir = mc->m.mnt_dir;
				remnt.mnt_type = mc->m.mnt_type;
				remnt.mnt_opts = "ro";
				remnt.mnt_freq = 0;
				remnt.mnt_passno = 0;
				update_mtab(node, &remnt);
			}
			return 0;
		} else if (errno != EBUSY) {
			perror("remount");
			fprintf(stderr,
				_("umount: could not remount %s read-only\n"),
				spec);
		}
	}

	loopdev = 0;
	if (res >= 0) {

		if (verbose)
			printf (_("%s has been unmounted\n"), spec);


		if (mc) {
			char *optl;


			if (streq(mc->m.mnt_type, "loop")) {
				loopdev = spec;
				goto gotloop;
			}


			optl = mc->m.mnt_opts ? xstrdup(mc->m.mnt_opts) : "";
			for (optl = strtok (optl, ","); optl;
			     optl = strtok (NULL, ",")) {
				if (!strncmp(optl, "loop=", 5)) {
					loopdev = optl+5;
					goto gotloop;
				}
			}
		} else {


			if ((mc = getmntoptfile (spec)) != NULL)
				node = mc->m.mnt_dir;
		}


		if (myloop)
			loopdev = spec;
	}
 gotloop:
	if (loopdev && !is_loop_autoclear(loopdev))
		del_loop(loopdev);

 writemtab:
	if (!nomtab &&
	    (umnt_err == 0 || umnt_err == EINVAL || umnt_err == ENOENT)) {
#ifdef HAVE_LIBMOUNT_MOUNT
		struct libmnt_update *upd = mnt_new_update();

		if (upd && !mnt_update_set_fs(upd, 0, node, NULL)) {
			struct libmnt_lock *lc = init_libmount_lock(
						mnt_update_get_filename(upd));
			mnt_update_table(upd, lc);
			init_libmount_lock(NULL);
		}
		mnt_free_update(upd);
#else
		update_mtab (node, NULL);
#endif
	}

	if (res >= 0)
		return 0;
	if (umnt_err)
		complain(umnt_err, node);
	return 1;
}
