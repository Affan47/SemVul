whitelisted_xattr (const char *key)
{
        if (!key)
                return 0;

        if (strcmp (POSIX_ACL_ACCESS_XATTR, key) == 0)
                return 1;
        if (strcmp (POSIX_ACL_DEFAULT_XATTR, key) == 0)
                return 1;
        return 0;
}
