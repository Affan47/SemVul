msync_bytes(const fr_extent<ft_uoff> & extent) const
{
    ft_uoff mem_offset = extent.second.user_data;
    ft_size mem_length = (ft_size) extent.second.length;
    int err;
    if ((err = msync((char *)storage_mmap + mem_offset, mem_length, MS_SYNC)) != 0) {
        ff_log(FC_WARN, errno, "I/O error in %s msync(address + %"FT_ULL", length = %"FT_ULL")",
                label[FC_STORAGE], (ft_ull)mem_offset, (ft_ull)mem_length);
        err = 0;
    }
    return err;
}
