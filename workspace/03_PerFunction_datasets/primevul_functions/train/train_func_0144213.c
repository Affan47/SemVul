void sc_ensure_shared_snap_mount(void)
{
	if (!is_mounted_with_shared_option("/")
	    && !is_mounted_with_shared_option(SNAP_MOUNT_DIR)) {


		sc_do_mount(SNAP_MOUNT_DIR, SNAP_MOUNT_DIR, "none",
			    MS_BIND | MS_REC, 0);
		sc_do_mount("none", SNAP_MOUNT_DIR, NULL, MS_SHARED | MS_REC,
			    NULL);
	}
}
