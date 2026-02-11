lcrt_user_find_unused_label(struct lcrt_window *lwindow,
    const char *keyword , char *label )
{
    int i;

    if (!lwindow || !keyword || !label)
        return LCRTE_INVAL;

    strcpy(label, keyword);

    if (lcrt_user_find_by_name(&lwindow->u_config, keyword) != NULL) {
        for (i = 1; i <= LCRT_MAX_LABEL; i++) {
            sprintf(label, "%s (%d)", keyword, i);
            if (lcrt_user_find_by_name(&lwindow->u_config, label) == NULL)
                return LCRTE_OK;
        };
    }
    return LCRTE_OK;
}
