generic_vendor_parse(char *line, sigar_sys_info_t *info)
{
    char *ptr;
    int len = 0;

    while (*line) {
        SIGAR_SKIP_SPACE(line);
        if (!isdigit(*line)) {
            ++line;
            continue;
        }

        ptr = line;
        while ((isdigit(*ptr) || (*ptr == '.'))) {
            ++ptr;
            ++len;
        }

        if (len) {

            if (len > sizeof(info->vendor_version)) {
                continue;
            }
            memcpy(info->vendor_version, line, len);
            info->vendor_version[len] = '\0';
            return;
        }
    }
}
