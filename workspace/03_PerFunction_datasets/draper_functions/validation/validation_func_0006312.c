gf_auth_init (xlator_t *xl, dict_t *auth_modules)
{
        int ret = 0;
        auth_handle_t *handle = NULL;
        data_pair_t *pair = NULL;

        dict_foreach (auth_modules, init, &ret);
        if (ret)
                goto out;

        pair = auth_modules->members_list;
        while (pair) {
                handle = data_to_ptr (pair->value);
                if (!handle) {
                        pair = pair->next;
                        continue;
                }

                list_add_tail (&(handle->vol_opt->list),
                               &(xl->volume_options));
                ret = xlator_options_validate_list (xl, xl->options,
                                                    handle->vol_opt, NULL);

                if (ret)
                        gf_log ("authenticate", GF_LOG_ERROR,
                                "volume option validation failed");

                pair = pair->next;
        }

out:
        if (ret) {
                gf_log (xl->name, GF_LOG_ERROR, "authentication init failed");
                dict_foreach (auth_modules, fini, &ret);
                ret = -1;
        }
        return ret;
}
