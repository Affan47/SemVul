ff_arch_linux_mem_system_free() {
    FILE * f = fopen("/proc/meminfo", "r");
    if (f == NULL) {
        ff_log(FC_WARN, errno, "failed to open /proc/meminfo, maybe /proc is not mounted?");
        return 0;
    }
    char label[256], unit[8];
    ft_ull n_ull = 0, scale;
    ft_uoff total = 0, n;
    ft_uint left = 3;
    int err;

    while (left != 0) {
        if ((err = fscanf(f, "%256s %"FT_ULL" %8s\n", label, & n_ull, unit)) <= 0) {
            if (ferror(f))
                ff_log(FC_WARN, errno, "error reading /proc/meminfo");
            break;
        }
        if (err != 3)
            continue;

        label[255] = '\0';
        unit[7] = '\0';

        if (strcmp(label, "MemFree:") && strcmp(label, "Buffers:") && strcmp(label, "Cached:"))
            continue;
        switch (unit[0]) {
            case 'k': scale = 10; break;
            case 'M': scale = 20; break;
            case 'G': scale = 30; break;
            case 'T': scale = 40; break;
            case 'P': scale = 50; break;
            case 'E': scale = 60; break;
            case 'Z': scale = 70; break;
            case 'Y': scale = 80; break;
            default: scale = 0; break;
        }

        if (scale >= 8*sizeof(ft_ull) || n_ull > (ft_ull)-1 >> scale)
            n_ull = (ft_ull)-1;
        else
            n_ull <<= scale;

        n = (ft_uoff) n_ull;

        if (n < 0 || n_ull != (ft_ull) n || n > (ft_uoff)-1 - total) {
            total = (ft_uoff)-1;
            break;
        }
        total += n;
        left--;
    }
    if (fclose(f) != 0)
        ff_log(FC_WARN, errno, "error closing /proc/meminfo");
    return total;
}
