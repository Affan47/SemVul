static bool block_xattr(struct lo_data *lo, const char *name)
{


    if (lo->user_posix_acl) {
        return false;
    }
    if (!strcmp(name, "system.posix_acl_access") ||
        !strcmp(name, "system.posix_acl_default"))
            return true;

    return false;
}
