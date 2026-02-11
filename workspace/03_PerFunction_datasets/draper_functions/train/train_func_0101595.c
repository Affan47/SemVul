create_struct3(void)
{
    misc5_struct3_hndl *str3hndl;
    herr_t ret;

    str3hndl = HDmalloc(sizeof(misc5_struct3_hndl));
    CHECK(str3hndl,NULL,"malloc");

    str3hndl->st3h_base = H5Tcreate(H5T_COMPOUND, sizeof(misc5_struct3));
    CHECK(str3hndl->st3h_base, FAIL, "H5Tcreate");

    ret = H5Tinsert(str3hndl->st3h_base, "st3_el1", HOFFSET( misc5_struct3, st3_el1), H5T_NATIVE_INT);
    CHECK(ret,FAIL,"H5Tinsert");

    str3hndl->st3h_id=H5Tvlen_create(str3hndl->st3h_base);
    CHECK(str3hndl->st3h_id,FAIL,"H5Tvlen_create");

    return(str3hndl);
}
