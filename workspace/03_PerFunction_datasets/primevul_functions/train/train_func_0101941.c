__debug_dir_hdr(struct zzip_dir_hdr *hdr)
{
    if (sizeof(struct zzip_dir_hdr) > sizeof(struct zzip_disk_entry))
        { WARN1("internal sizeof-mismatch may break wreakage"); }


    if (((zzip_off_t) hdr) & 3)
    {
        NOTE1("this machine's malloc(3) returns sth. not u32-aligned");
    }


}
