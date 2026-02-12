virSecuritySELinuxMCSGetProcessRange(char **sens,
                                     int *catMin,
                                     int *catMax)
{
    char *ourSecContext = NULL;
    context_t ourContext = NULL;
    char *cat = NULL;
    char *tmp;
    const char *contextRange;
    int ret = -1;

    if (getcon_raw(&ourSecContext) < 0) {
        virReportSystemError(errno, "%s",
                             _("Unable to get current process SELinux context"));
        goto cleanup;
    }
    if (!(ourContext = context_new(ourSecContext))) {
        virReportSystemError(errno,
                             _("Unable to parse current SELinux context '%s'"),
                             ourSecContext);
        goto cleanup;
    }
    if (!(contextRange = context_range_get(ourContext)))
        contextRange = "s0";

    *sens = g_strdup(contextRange);


    tmp = strchr(*sens, ':');
    if (tmp) {
        *tmp = '\0';
        cat = tmp + 1;
    }

    if ((tmp = strchr(*sens, '-')))
        *tmp = '\0';


    if (!cat) {
        *catMin = 0;
        *catMax = 1023;
        ret = 0;
        goto cleanup;
    }


    tmp = cat;
    if (tmp[0] != 'c') {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Cannot parse category in %s"),
                       cat);
        goto cleanup;
    }
    tmp++;
    if (virStrToLong_i(tmp, &tmp, 10, catMin) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Cannot parse category in %s"),
                       cat);
        goto cleanup;
    }


    if (!tmp[0]) {
        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
                       _("No category range available"));
        goto cleanup;
    }


    if (tmp[0] != '.') {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Cannot parse category in %s"),
                       cat);
        goto cleanup;
    }
    tmp++;
    if (tmp[0] != 'c') {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Cannot parse category in %s"),
                       cat);
        goto cleanup;
    }
    tmp++;
    if (virStrToLong_i(tmp, &tmp, 10, catMax) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Cannot parse category in %s"),
                       cat);
        goto cleanup;
    }

    ret = 0;

 cleanup:
    if (ret < 0)
        VIR_FREE(*sens);
    freecon(ourSecContext);
    context_free(ourContext);
    return ret;
}
