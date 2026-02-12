uc_err uc_hook_del(uc_engine *uc, uc_hook hh)
{
    int i;
    struct hook *hook = (struct hook *)hh;

    UC_INIT(uc);


    for (i = 0; i < UC_HOOK_MAX; i++) {
        if (list_exists(&uc->hook[i], (void *)hook)) {
            hook->to_delete = true;
            uc->hooks_count[i]--;
            list_append(&uc->hooks_to_del, hook);
        }
    }

    return UC_ERR_OK;
}
