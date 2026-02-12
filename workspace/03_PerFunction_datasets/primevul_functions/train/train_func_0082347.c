static int SavePackageDescriptionToDebugDump(const char *dump_dir_name)
{
    struct dump_dir *dd = dd_opendir(dump_dir_name,  0);
    if (!dd)
        return 1;

    char *analyzer = dd_load_text(dd, FILENAME_ANALYZER);
    if (!strcmp(analyzer, "Kerneloops"))
    {
        dd_save_text(dd, FILENAME_PACKAGE, "kernel");
        dd_save_text(dd, FILENAME_COMPONENT, "kernel");
        dd_close(dd);
        free(analyzer);
        return 0;
    }
    free(analyzer);

    char *cmdline = NULL;
    char *executable = NULL;
    char *rootdir = NULL;
    char *package_short_name = NULL;
    struct pkg_envra *pkg_name = NULL;
    char *component = NULL;
    int error = 1;


    cmdline = dd_load_text_ext(dd, FILENAME_CMDLINE, DD_FAIL_QUIETLY_ENOENT);
    executable = dd_load_text(dd, FILENAME_EXECUTABLE);
    rootdir = dd_load_text_ext(dd, FILENAME_ROOTDIR,
                               DD_FAIL_QUIETLY_ENOENT | DD_LOAD_TEXT_RETURN_NULL_ON_FAILURE);


    dd_close(dd);

    if (is_path_blacklisted(executable))
    {
        log("Blacklisted executable '%s'", executable);
        goto ret;
    }

    pkg_name = rpm_get_package_nvr(executable, rootdir);
    if (!pkg_name)
    {
        if (settings_bProcessUnpackaged)
        {
            log_info("Crash in unpackaged executable '%s', "
                      "proceeding without packaging information", executable);
            goto ret0;
        }
        log("Executable '%s' doesn't belong to any package"
		" and ProcessUnpackaged is set to 'no'",
		executable
        );
        goto ret;
    }


    const char *basename = strrchr(executable, '/');
    if (basename)
        basename++;
    else
        basename = executable;


    if (g_list_find_custom(settings_Interpreters, basename, (GCompareFunc)g_strcmp0))
    {
        struct pkg_envra *script_pkg = get_script_name(cmdline, &executable);

        if (is_path_blacklisted(executable))
        {
            log("Blacklisted executable '%s'", executable);
            goto ret;
        }
        if (!script_pkg)
        {


            if (!settings_bProcessUnpackaged)
            {
                log("Interpreter crashed, but no packaged script detected: '%s'", cmdline);
                goto ret;
            }


            goto ret0;
        }

        free_pkg_envra(pkg_name);
        pkg_name = script_pkg;
    }

    package_short_name = xasprintf("%s", pkg_name->p_name);
    log_info("Package:'%s' short:'%s'", pkg_name->p_nvr, package_short_name);


    if (g_list_find_custom(settings_setBlackListedPkgs, package_short_name, (GCompareFunc)g_strcmp0))
    {
        log("Blacklisted package '%s'", package_short_name);
        goto ret;
    }

    if (settings_bOpenGPGCheck)
    {
        if (!rpm_chk_fingerprint(package_short_name))
        {
            log("Package '%s' isn't signed with proper key", package_short_name);
            goto ret;
        }


    }

    component = rpm_get_component(executable, rootdir);

    dd = dd_opendir(dump_dir_name,  0);
    if (!dd)
        goto ret;

    if (pkg_name)
    {
        dd_save_text(dd, FILENAME_PACKAGE, pkg_name->p_nvr);
        dd_save_text(dd, FILENAME_PKG_EPOCH, pkg_name->p_epoch);
        dd_save_text(dd, FILENAME_PKG_NAME, pkg_name->p_name);
        dd_save_text(dd, FILENAME_PKG_VERSION, pkg_name->p_version);
        dd_save_text(dd, FILENAME_PKG_RELEASE, pkg_name->p_release);
        dd_save_text(dd, FILENAME_PKG_ARCH, pkg_name->p_arch);
    }

    if (component)
        dd_save_text(dd, FILENAME_COMPONENT, component);

    dd_close(dd);

 ret0:
    error = 0;
 ret:
    free(cmdline);
    free(executable);
    free(rootdir);
    free(package_short_name);
    free_pkg_envra(pkg_name);
    free(component);

    return error;
}
