void helper_uc_tracecode(int32_t size, uc_hook_idx index, void *handle,
                         int64_t address)
{
    struct uc_struct *uc = handle;
    struct list_item *cur;
    struct hook *hook;
    int hook_flags =
        index &
        UC_HOOK_FLAG_MASK;


    index = index & UC_HOOK_IDX_MASK;


    if (uc->stop_request && !(hook_flags & UC_HOOK_FLAG_NO_STOP)) {
        return;
    }

    for (cur = uc->hook[index].head;
         cur != NULL && (hook = (struct hook *)cur->data); cur = cur->next) {
        if (hook->to_delete) {
            continue;
        }


        if (size == 0) {
            if (index == UC_HOOK_CODE_IDX && uc->count_hook) {

                ((uc_cb_hookcode_t)hook->callback)(uc, address, size,
                                                   hook->user_data);
            }

            return;
        }

        if (HOOK_BOUND_CHECK(hook, (uint64_t)address)) {
            ((uc_cb_hookcode_t)hook->callback)(uc, address, size,
                                               hook->user_data);
        }


        if (uc->stop_request && !(hook_flags & UC_HOOK_FLAG_NO_STOP)) {
            break;
        }
    }
}
