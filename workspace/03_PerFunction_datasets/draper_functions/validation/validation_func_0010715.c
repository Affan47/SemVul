dvdrw_device_finish(Device *dself)
{
    DvdRwDevice *self = DVDRW_DEVICE(dself);
    VfsDevice *vself = VFS_DEVICE(dself);
    gboolean result;
    DeviceClass *parent_class = DEVICE_CLASS(g_type_class_peek_parent(DVDRW_DEVICE_GET_CLASS(dself)));
    DeviceAccessMode mode;

    g_debug("Finish DVDRW device");


    mode = dself->access_mode;

    result = parent_class->finish(dself);

    if (mode == ACCESS_READ) {
	unmount_disc(self);
    }

    if (!result || device_in_error(dself)) {
	return FALSE;
    }

    if (mode == ACCESS_WRITE) {
	result = burn_disc(self);

	if (result && !self->keep_cache) {
	    delete_vfs_files(vself);
	}

	return result;
    }

    return TRUE;
}
