pam_getenv (pam_handle_t *pamh, const char *name)
{
    int i;

    if (pamh == NULL || name == NULL)
        return NULL;

    for (i = 0; pamh->envlist[i]; i++)
    {
        const char *value;
        value = get_env_value (pamh->envlist[i], name);
        if (value)
            return value;
    }

    return NULL;
}
