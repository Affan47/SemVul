dwarf_global_name_offsets(Dwarf_Global global,
    char **ret_name,
    Dwarf_Off * die_offset,
    Dwarf_Off * cu_die_offset,
    Dwarf_Error * error)
{
    Dwarf_Global_Context con = 0;
    Dwarf_Debug dbg = 0;
    Dwarf_Off cuhdr_off = 0;

    if (global == NULL) {
        _dwarf_error(NULL, error, DW_DLE_GLOBAL_NULL);
        return DW_DLV_ERROR;
    }

    con = global->gl_context;
    if (con == NULL) {
        _dwarf_error(NULL, error, DW_DLE_GLOBAL_CONTEXT_NULL);
        return DW_DLV_ERROR;
    }

    cuhdr_off = con->pu_offset_of_cu_header;


#define MIN_CU_HDR_SIZE 10
    dbg = con->pu_dbg;
    if (!dbg || dbg->de_magic != DBG_IS_VALID) {
        _dwarf_error_string(NULL, error, DW_DLE_DBG_NULL,
            "DW_DLE_DBG_NULL: Either null or it contains"
            "a stale Dwarf_Debug pointer");
        return DW_DLV_ERROR;
    }

    if (dbg->de_debug_info.dss_size &&
        ((cuhdr_off + MIN_CU_HDR_SIZE) >=
        dbg->de_debug_info.dss_size)) {
        dwarfstring m;

        dwarfstring_constructor(&m);
        build_off_end_msg(cuhdr_off,cuhdr_off+MIN_CU_HDR_SIZE,
            dbg->de_debug_info.dss_size,&m);
        _dwarf_error_string(dbg, error, DW_DLE_OFFSET_BAD,
            dwarfstring_string(&m));
        dwarfstring_destructor(&m);
        return DW_DLV_ERROR;
    }
#undef MIN_CU_HDR_SIZE


    if (die_offset) {
        if (global->gl_named_die_offset_within_cu) {
            *die_offset = global->gl_named_die_offset_within_cu +
                cuhdr_off;
        } else {
            *die_offset = 0;
        }
    }
    *ret_name = (char *) global->gl_name;
    if (cu_die_offset) {

        int cres = 0;
        Dwarf_Unsigned headerlen = 0;
        int res = _dwarf_load_debug_info(dbg, error);

        if (res != DW_DLV_OK) {
            return res;
        }


        if ((cuhdr_off + 10) >= dbg->de_debug_info.dss_size) {
            dwarfstring m;

            dwarfstring_constructor(&m);
            build_off_end_msg(cuhdr_off,cuhdr_off+10,
                dbg->de_debug_info.dss_size,&m);
            _dwarf_error_string(dbg, error, DW_DLE_OFFSET_BAD,
                dwarfstring_string(&m));
            dwarfstring_destructor(&m);
            return DW_DLV_ERROR;
        }
        cres = _dwarf_length_of_cu_header(dbg, cuhdr_off,true,
            &headerlen,error);
        if (cres != DW_DLV_OK) {
            return cres;
        }
        *cu_die_offset = cuhdr_off + headerlen;
    }
    return DW_DLV_OK;
}
