static struct pkg_envra *get_script_name(const char *cmdline, char **executable)
{


    struct pkg_envra *script_pkg = NULL;
    char *script_name = get_argv1_if_full_path(cmdline);
    if (script_name)
    {
        script_pkg = rpm_get_package_nvr(script_name, NULL);
        if (script_pkg)
        {


            *executable = script_name;
        }
    }

    return script_pkg;
}
