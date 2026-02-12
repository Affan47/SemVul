lr_yum_download_repomd(LrHandle *handle,
                       LrMetalink *metalink,
                       int fd,
                       GError **err)
{
    int ret = TRUE;
    GError *tmp_err = NULL;

    assert(!err || *err == NULL);

    g_debug("%s: Downloading repomd.xml via mirrorlist", __func__);

    GSList *checksums = NULL;
    if (metalink && (handle->checks & LR_CHECK_CHECKSUM)) {
        lr_get_best_checksum(metalink, &checksums);
    }

    CbData *cbdata = cbdata_new(handle->user_data,
                            NULL,
                            handle->user_cb,
                            handle->hmfcb,
                            "repomd.xml");

    LrDownloadTarget *target = lr_downloadtarget_new(handle,
                                                     "repodata/repomd.xml",
                                                     NULL,
                                                     fd,
                                                     NULL,
                                                     checksums,
                                                     0,
                                                     0,
                                                     (handle->user_cb) ? progresscb : NULL,
                                                     cbdata,
                                                     NULL,
                                                     (handle->hmfcb) ? hmfcb : NULL,
                                                     NULL,
                                                     0,
                                                     0,
                                                     NULL,
                                                     TRUE,
                                                     FALSE);

    ret = lr_download_target(target, &tmp_err);
    assert((ret && !tmp_err) || (!ret && tmp_err));

    if (cbdata)
        cbdata_free(cbdata);

    if (tmp_err) {
        g_propagate_prefixed_error(err, tmp_err,
                                   "Cannot download repomd.xml: ");
    } else if (target->err) {
        assert(0);
        ret = FALSE;
        g_set_error(err, LR_DOWNLOADER_ERROR, target->rcode,
                    "Cannot download repomd.xml: %s",target->err);
    } else {


        lr_free(handle->used_mirror);
        handle->used_mirror = g_strdup(target->usedmirror);
    }

    lr_downloadtarget_free(target);

    if (!ret) {

        g_debug("%s: repomd.xml download was unsuccessful", __func__);
    }

    return ret;
}
