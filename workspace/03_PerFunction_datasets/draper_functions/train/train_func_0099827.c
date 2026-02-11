header_hrdisk(struct variable *vp,
              oid * name,
              size_t * length,
              int exact, size_t * var_len, WriteMethod ** write_method)
{
#define HRDISK_ENTRY_NAME_LENGTH	11
    oid             newname[MAX_OID_LEN];
    int             disk_idx, LowIndex = -1;
    int             result;

    DEBUGMSGTL(("host/hr_disk", "var_hrdisk: "));
    DEBUGMSGOID(("host/hr_disk", name, *length));
    DEBUGMSG(("host/hr_disk", " %d\n", exact));

    memcpy((char *) newname, (char *) vp->name,
           (int) vp->namelen * sizeof(oid));


    Init_HR_Disk();
    for (;;) {
        disk_idx = Get_Next_HR_Disk();
        DEBUGMSGTL(("host/hr_disk", "... index %d\n", disk_idx));
        if (disk_idx == -1)
            break;
        newname[HRDISK_ENTRY_NAME_LENGTH] = disk_idx;
        result =
            snmp_oid_compare(name, *length, newname,
                             (int) vp->namelen + 1);
        if (exact && (result == 0)) {
            LowIndex = disk_idx;
            Save_HR_Disk_Specific();
            break;
        }
        if ((!exact && (result < 0)) &&
            (LowIndex == -1 || disk_idx < LowIndex)) {
            LowIndex = disk_idx;
            Save_HR_Disk_Specific();
#ifdef HRD_MONOTONICALLY_INCREASING
            break;
#endif
        }
    }

    if (LowIndex == -1) {
        DEBUGMSGTL(("host/hr_disk", "... index out of range\n"));
        return (MATCH_FAILED);
    }

    newname[HRDISK_ENTRY_NAME_LENGTH] = LowIndex;
    memcpy((char *) name, (char *) newname,
           ((int) vp->namelen + 1) * sizeof(oid));
    *length = vp->namelen + 1;
    *write_method = (WriteMethod*)0;
    *var_len = sizeof(long);

    DEBUGMSGTL(("host/hr_disk", "... get disk stats "));
    DEBUGMSGOID(("host/hr_disk", name, *length));
    DEBUGMSG(("host/hr_disk", "\n"));

    return LowIndex;
}
