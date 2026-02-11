_rename_dev_node(const char *old_name, const char *new_name,
			    int warn_if_udev_failed)
{
	char oldpath[PATH_MAX];
	char newpath[PATH_MAX];
	struct stat info;

	_build_dev_path(oldpath, sizeof(oldpath), old_name);
	_build_dev_path(newpath, sizeof(newpath), new_name);

	if (stat(newpath, &info) == 0) {
		if (!S_ISBLK(info.st_mode)) {
			log_error("A non-block device file at '%s' "
				  "is already present", newpath);
			return 0;
		}
		else if (_warn_if_op_needed(warn_if_udev_failed)) {
			if (stat(oldpath, &info) < 0 &&
				 errno == ENOENT)

				return 1;
			else {
				log_warn("The node %s should have been renamed to %s "
					 "by udev but old node is still present. "
					 "Falling back to direct old node removal.",
					 oldpath, newpath);
				return _rm_dev_node(old_name, 0);
			}
		}

		if (unlink(newpath) < 0) {
			if (errno == EPERM) {

				return 1;
			}
			log_error("Unable to unlink device node for '%s'",
				  new_name);
			return 0;
		}
	}
	else if (_warn_if_op_needed(warn_if_udev_failed))
		log_warn("The node %s should have been renamed to %s "
			 "by udev but new node is not present. "
			 "Falling back to direct node rename.",
			 oldpath, newpath);

	if (rename(oldpath, newpath) < 0) {
		log_error("Unable to rename device node from '%s' to '%s'",
			  old_name, new_name);
		return 0;
	}

	log_debug("Renamed %s to %s", oldpath, newpath);

	return 1;
}
