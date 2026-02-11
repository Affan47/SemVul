ndmp_connection_scsi_open(
	NDMPConnection *self,
	gchar *device)
{
    g_assert(!self->startup_err);

    NDMP_TRANS(self, ndmp4_scsi_open)
	request->device = device;
	NDMP_CALL(self);
	NDMP_FREE();
    NDMP_END
    return TRUE;
}
