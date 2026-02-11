check_missing_plugins(GstCaps* caps)
{
    GstElementFactory * factory = swfdec_gst_get_element_factory(caps);

    if (factory) {
        gst_object_unref(factory);
        return true;
    }

#ifdef HAVE_GST_PBUTILS_INSTALL_PLUGINS_H
    gst_pb_utils_init();


    if (!gst_install_plugins_supported()) {
        log_error(_("Missing plugin, but plugin installing not supported."
                    " Will try anyway, but expect failure."));
    }

    char* detail = gst_missing_decoder_installer_detail_new(caps);
    if (!detail) {
        log_error(_("Missing plugin, but failed to convert it to gst"
                    " missing plugin detail."));
        return false;
    }

    char* details[] =  { detail, 0 };

    GstInstallPluginsReturn ret = gst_install_plugins_sync(details, NULL);
    g_free(details[0]);


    if (ret == GST_INSTALL_PLUGINS_SUCCESS) {
        if (! gst_update_registry()) {
            log_error(_("gst_update_registry failed. You'll need to "
                        "restart Gnash to use the new plugins."));
        }

        return true;
    }
#else
    log_error(_("Missing plugin, but automatic plugin installation not "
                "available."));
#endif

    return false;
}

}
