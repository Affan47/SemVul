loop_check(const char **spec, const char **type, int *flags,
	   int *loop, const char **loopdev, const char **loopfile,
	   const char *node) {
  int looptype;
  uintmax_t offset = 0, sizelimit = 0;
  struct loopdev_cxt lc;
  char *pwd = NULL;
  int ret = EX_FAIL;


  *loopdev = opt_loopdev;

  looptype = (*type && strncmp("lo@", *type, 3) == 0);
  if (looptype) {
    if (*loopdev)
      error(_("mount: loop device specified twice"));
    *loopdev = *type + 3;
    *type = opt_vfstype;
  } else if (opt_vfstype) {
    if (*type)
      error(_("mount: type specified twice"));
    else
      *type = opt_vfstype;
  }

  *loop = ((*flags & MS_LOOP) || *loopdev || opt_offset || opt_sizelimit);
  *loopfile = *spec;


  if (!*loop && !(*flags & (MS_BIND | MS_MOVE | MS_PROPAGATION)) &&
      (!*type || strcmp(*type, "auto") == 0 || fsprobe_known_fstype(*type))) {

    struct stat st;
    if (stat(*loopfile, &st) == 0)
      *loop = S_ISREG(st.st_mode);
  }

  if (*loop) {
    *flags |= MS_LOOP;
    if (fake) {
      if (verbose)
	printf(_("mount: skipping the setup of a loop device\n"));
    } else {
      int loop_opts = 0;


      if (get_linux_version() >= KERNEL_VERSION(2, 6, 37) ||
	  mtab_is_writable() == 0) {

	if (verbose)
	  printf(_("mount: enabling autoclear loopdev flag\n"));
	loop_opts = LO_FLAGS_AUTOCLEAR;
      }

      if (*flags & MS_RDONLY)
        loop_opts |= LO_FLAGS_READ_ONLY;

      if (opt_offset && parse_offset(&opt_offset, &offset)) {
        error(_("mount: invalid offset '%s' specified"), opt_offset);
        return EX_FAIL;
      }
      if (opt_sizelimit && parse_offset(&opt_sizelimit, &sizelimit)) {
        error(_("mount: invalid sizelimit '%s' specified"), opt_sizelimit);
        return EX_FAIL;
      }

      if (is_mounted_same_loopfile(node, *loopfile, offset)) {
        error(_("mount: according to mtab %s is already mounted on %s as loop"), *loopfile, node);
        return EX_FAIL;
      }

      if (opt_encryption) {
        error("mount: %s", _("encryption not supported, use cryptsetup(8) instead"));
        return EX_FAIL;
      }

      loopcxt_init(&lc, 0);


      if (*loopdev && **loopdev)
	loopcxt_set_device(&lc, *loopdev);

      do {
	int rc;

        if ((!*loopdev || !**loopdev) && loopcxt_find_unused(&lc) == 0)
	    *loopdev = loopcxt_strdup_device(&lc);

	if (!*loopdev) {
	  error(_("mount: failed to found free loop device"));
	  loopcxt_deinit(&lc);
	  goto err;
	}
	if (verbose)
	  printf(_("mount: going to use the loop device %s\n"), *loopdev);

	rc = loopcxt_set_backing_file(&lc, *loopfile);

	if (!rc && offset)
	  rc = loopcxt_set_offset(&lc, offset);
	if (!rc && sizelimit)
	  rc = loopcxt_set_sizelimit(&lc, sizelimit);
	if (!rc)
	  loopcxt_set_flags(&lc, loop_opts);

	if (rc) {
	   error(_("mount: %s: failed to set loopdev attributes"), *loopdev);
	   loopcxt_deinit(&lc);
	   goto err;
	}


	rc = loopcxt_setup_device(&lc);
	if (!rc)
	  break;

	if (rc != -EBUSY) {
	  error(_("mount: %s: failed setting up loop device: %m"), *loopfile);
	  if (!opt_loopdev) {
	    my_free(*loopdev);
	    *loopdev = NULL;
	  }
	  loopcxt_deinit(&lc);
	  goto err;
	}

	if (!opt_loopdev) {
	  if (verbose)
	    printf(_("mount: stolen loop=%s ...trying again\n"), *loopdev);
	    my_free(*loopdev);
	    *loopdev = NULL;
	    continue;
	}
	error(_("mount: stolen loop=%s"), *loopdev);
	loopcxt_deinit(&lc);
	goto err;

      } while (!*loopdev);

      if (verbose > 1)
	printf(_("mount: setup loop device successfully\n"));
      *spec = *loopdev;

      if (loopcxt_is_readonly(&lc))
        *flags |= MS_RDONLY;

      if (loopcxt_is_autoclear(&lc))

        *loop = 0;


      loopcxt_set_fd(&lc, -1, 0);
      loopcxt_deinit(&lc);
    }
  }

  ret = 0;
err:
  if (pwd) {
    char *p = pwd;
    while (*p)
      *p++ = '\0';
    free(pwd);
  }
  return ret;
}
