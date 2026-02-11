sync(void)
{
    if (the_name) {
        delete [] the_name;
    }
    if (the_cur) {
        delete [] the_cur;
    }
    if (cur_rec) {
        delete [] cur_rec;
    }
    char nam[NC_MAX_NAME];
    if (the_file
        && NcError::set_err(
                            nc_inq_varname(the_file->id(), the_id, nam)
                            ) == NC_NOERR) {
        the_name = new char[1 + strlen(nam)];
        strcpy(the_name, nam);
    } else {
        the_name = 0;
        return FALSE;
    }
    init_cur();
    return TRUE;
}
