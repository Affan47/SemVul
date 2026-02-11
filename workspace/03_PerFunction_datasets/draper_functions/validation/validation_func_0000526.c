ldbm_instance_config_instance_dir_set(void *arg, void *value, char *errorbuf, int phase, int apply)
{
    ldbm_instance *inst = (ldbm_instance *)arg;

    if (!apply) {
        return LDAP_SUCCESS;
    }

    if ((value == NULL) || (strlen(value) == 0))
    {
        inst->inst_dir_name = NULL;
        inst->inst_parent_dir_name = NULL;
    }
    else
    {
        char *dir = (char *)value;
        if (is_fullpath(dir))
        {
            char sep = get_sep(dir);
            char *p = strrchr(dir, sep);
            if (NULL == p)
            {
                inst->inst_parent_dir_name = NULL;
                inst->inst_dir_name = rel2abspath(dir);


            }
            else
            {
                *p = '\0';
                inst->inst_parent_dir_name = rel2abspath(dir);


                inst->inst_dir_name = slapi_ch_strdup(p+1);
                *p = sep;
            }
        }
        else
        {
            inst->inst_parent_dir_name = NULL;
            inst->inst_dir_name = slapi_ch_strdup(dir);
        }
    }
    return LDAP_SUCCESS;
}
