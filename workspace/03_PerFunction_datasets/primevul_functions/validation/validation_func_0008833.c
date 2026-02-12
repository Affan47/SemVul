static int intGetTdEntry(Header h, rpmtd td, headerGetFlags flags)
{
    indexEntry entry;
    int rc;


    entry = findEntry(h, td->tag, RPM_NULL_TYPE);
    if (entry == NULL) {

	return 0;
    }

    if (entry->info.type == RPM_I18NSTRING_TYPE && !(flags & HEADERGET_RAW))
	rc = copyI18NEntry(h, entry, td, flags);
    else
	rc = copyTdEntry(entry, td, flags);

    if (rc == 0)
	td->flags |= RPMTD_INVALID;


    return ((rc == 1) ? 1 : 0);
}
