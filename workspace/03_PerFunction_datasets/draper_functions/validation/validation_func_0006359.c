get_keys(struct mtree_writer *mtree, struct archive_entry *entry)
{
    int keys;

    keys = mtree->keys;
    if (mtree->set.keys == 0)
        return (keys);
    if ((mtree->set.keys & (F_GNAME | F_GID)) != 0 &&
         mtree->set.gid == archive_entry_gid(entry))
        keys &= ~(F_GNAME | F_GID);
    if ((mtree->set.keys & (F_UNAME | F_UID)) != 0 &&
         mtree->set.uid == archive_entry_uid(entry))
        keys &= ~(F_UNAME | F_UID);
    if (mtree->set.keys & F_FLAGS) {
        unsigned long set, clear;

        archive_entry_fflags(entry, &set, &clear);
        if (mtree->set.fflags_set == set &&
            mtree->set.fflags_clear == clear)
            keys &= ~F_FLAGS;
    }
    if ((mtree->set.keys & F_MODE) != 0 &&
         mtree->set.mode == (archive_entry_mode(entry) & 07777))
        keys &= ~F_MODE;

    switch (archive_entry_filetype(entry)) {
    case AE_IFLNK: case AE_IFSOCK: case AE_IFCHR:
    case AE_IFBLK: case AE_IFIFO:
        break;
    case AE_IFDIR:
        if ((mtree->set.keys & F_TYPE) != 0 &&
            mtree->set.type == AE_IFDIR)
            keys &= ~F_TYPE;
        break;
    case AE_IFREG:
    default:
        if ((mtree->set.keys & F_TYPE) != 0 &&
            mtree->set.type == AE_IFREG)
            keys &= ~F_TYPE;
        break;
    }

    return (keys);
}
