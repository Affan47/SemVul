H5FD_multi_sb_encode(H5FD_t *_file, char *name,
		     unsigned char *buf)
{
    H5FD_multi_t	*file = (H5FD_multi_t*)_file;
    haddr_t		memb_eoa;
    unsigned char	*p;
    size_t		nseen;
    size_t		i;
    H5FD_mem_t		m;
    static const char *func="H5FD_multi_sb_encode";


    H5Eclear2(H5E_DEFAULT);


    strncpy(name, "NCSAmulti", (size_t)8);
    name[8] = '\0';

    assert(7==H5FD_MEM_NTYPES);

    for (m=H5FD_MEM_SUPER; m<H5FD_MEM_NTYPES; m=(H5FD_mem_t)(m+1)) {
        buf[m-1] = (unsigned char)file->fa.memb_map[m];
    }
    buf[6] = 0;
    buf[7] = 0;


    nseen = 0;
    p = buf+8;
    assert(sizeof(haddr_t)<=8);
    UNIQUE_MEMBERS(file->fa.memb_map, mt) {
        memcpy(p, &(file->fa.memb_addr[mt]), sizeof(haddr_t));
        p += sizeof(haddr_t);
        memb_eoa = H5FDget_eoa(file->memb[mt], mt);
        memcpy(p, &memb_eoa, sizeof(haddr_t));
        p += sizeof(haddr_t);
        nseen++;
    } END_MEMBERS;
    if (H5Tconvert(H5T_NATIVE_HADDR, H5T_STD_U64LE, nseen*2, buf+8, NULL, H5P_DEFAULT)<0)
        H5Epush_ret(func, H5E_ERR_CLS, H5E_DATATYPE, H5E_CANTCONVERT, "can't convert superblock info", -1)


    p = buf + 8 + nseen*2*8;
    UNIQUE_MEMBERS(file->fa.memb_map, mt) {
        size_t n = strlen(file->fa.memb_name[mt]) + 1;
        strncpy((char *)p, file->fa.memb_name[mt], n);
        p += n;
        for (i=n; i%8; i++)
            *p++ = '\0';
    } END_MEMBERS;

    return 0;
}
