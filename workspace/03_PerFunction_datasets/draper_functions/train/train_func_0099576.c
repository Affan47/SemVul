load_mres(ulong siz, CVmImageLoaderMres *res_ifc)
{
    char buf[16];
    uint entry_cnt;
    long base_ofs;
    uint i;


    base_ofs = fp_->get_seek() + base_seek_ofs_;


    read_data(buf, 2, &siz);
    entry_cnt = osrp2(buf);


    for (i = 0 ; i < entry_cnt ; ++i)
    {
        uint32 entry_ofs;
        uint32 entry_size;
        uint entry_name_len;
        char name_buf[256];
        char *p;
        size_t rem;


        read_data(buf, 9, &siz);
        entry_ofs = t3rp4u(buf);
        entry_size = t3rp4u(buf + 4);
        entry_name_len = (uchar)*(buf + 8);


        read_data(name_buf, entry_name_len, &siz);


        name_buf[entry_name_len] = '\0';


        for (p = name_buf, rem = entry_name_len ; rem != 0 ; ++p, --rem)
             *p ^= 0xFF;


        res_ifc->add_resource(base_ofs + entry_ofs, entry_size,
                              name_buf, entry_name_len);
    }


    if (siz != 0)
        fp_->skip_ahead(siz);
}
