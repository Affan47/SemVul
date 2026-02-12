virStorageVolFDStreamCloseCb(virStreamPtr st G_GNUC_UNUSED,
                             void *opaque)
{
    virThread thread;

    if (virThreadCreateFull(&thread, false, virStorageVolPoolRefreshThread,
                            "vol-refresh", false, opaque) < 0) {

        VIR_ERROR(_("Failed to create thread to handle pool refresh"));
        goto error;
    }
    return;

 error:
    virStorageVolPoolRefreshDataFree(opaque);
}
