ifTable_commit(ifTable_rowreq_ctx * rowreq_ctx)
{
    int             rc = MFD_SUCCESS;
    int             save_flags;

    DEBUGMSGTL(("verbose:ifTable:ifTable_commit", "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);


    save_flags = rowreq_ctx->column_set_flags;
    rowreq_ctx->column_set_flags = 0;


    if (save_flags & COLUMN_IFADMINSTATUS_FLAG) {
        save_flags &= ~COLUMN_IFADMINSTATUS_FLAG;


        rc = netsnmp_access_interface_entry_set_admin_status(rowreq_ctx->
                                                             data.ifentry,
                                                             rowreq_ctx->
                                                             data.
                                                             ifAdminStatus);
        if (0 != rc) {
            snmp_log(LOG_ERR,
                     "ifTable column ifAdminStatus commit failed\n");
        } else {


            rowreq_ctx->column_set_flags |= COLUMN_IFADMINSTATUS_FLAG;
        }
    }


    if (MFD_SUCCESS == rc) {
        rowreq_ctx->rowreq_flags |= MFD_ROW_DIRTY;
    }

    if (save_flags) {
        snmp_log(LOG_ERR, "unhandled columns (0x%x) in commit\n",
                 save_flags);
        return MFD_ERROR;
    }

    return rc;
}
