_kernel_cmdline_match(const char *const *proc_cmdline, const char *pattern)
{
    if (proc_cmdline) {
        gboolean has_equal   = (!!strchr(pattern, '='));
        gsize    pattern_len = strlen(pattern);

        for (; proc_cmdline[0]; proc_cmdline++) {
            const char *c = proc_cmdline[0];

            if (has_equal) {

                if (nm_streq(c, pattern))
                    return TRUE;
                continue;
            }


            if (strncmp(c, pattern, pattern_len) == 0 && NM_IN_SET(c[pattern_len], '\0', '='))
                return TRUE;
        }
    }

    return FALSE;
}
