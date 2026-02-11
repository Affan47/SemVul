_get_uid_and_gid_for_user (const char *username,
                           uid_t      *uid,
                           gid_t      *gid)
{
        struct passwd *passwd_entry;

        g_assert (username != NULL);
        g_assert (uid != NULL);
        g_assert (gid != NULL);

        errno = 0;
        gdm_get_pwent_for_name (username, &passwd_entry);

        if (passwd_entry == NULL) {
                return FALSE;
        }

        *uid = passwd_entry->pw_uid;
        *gid = passwd_entry->pw_gid;

        return TRUE;
}
