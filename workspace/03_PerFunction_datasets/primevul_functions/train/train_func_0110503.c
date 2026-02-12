iscsi_allocmap_set_unallocated(IscsiLun *iscsilun, int64_t offset,
                               int64_t bytes)
{


    iscsi_allocmap_update(iscsilun, offset, bytes, false, true);
}
