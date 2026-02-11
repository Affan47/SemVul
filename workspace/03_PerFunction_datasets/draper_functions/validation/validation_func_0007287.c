flush_bytes()
{
    int err = 0;
    do {
        if (ui() != NULL)
            ui()->show_io_flush();

        if (simulate_run())
            break;

#if 1
        if ((err = msync(storage_mmap, storage_mmap_size, MS_SYNC)) != 0) {
            ff_log(FC_WARN, errno, "I/O error in %s msync(address + %"FT_ULL", length = %"FT_ULL")",
                    label[FC_STORAGE], (ft_ull)0, (ft_ull)storage_mmap_size);
            err = 0;
        }
#else
        fr_vector<ft_uoff>::const_iterator begin = primary_storage().begin(), iter, end = primary_storage().end();
        for (iter = begin; iter != end; ++iter)
            msync_bytes(*iter);
        if (secondary_storage().length() != 0)
            msync_bytes(secondary_storage());
#endif

        (void) sync();
#if 0
        if (err != 0) {
            ff_log(FC_WARN, errno, "I/O error in sync()");
            err = 0;
        }
#endif
    } while (0);
    return err;
}
