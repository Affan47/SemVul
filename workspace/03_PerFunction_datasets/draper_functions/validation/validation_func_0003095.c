gnc_split_register_get_tcredit_label (VirtualLocation virt_loc,
                                      gpointer user_data)
{
    SplitRegister *reg = user_data;
    SRInfo *info = gnc_split_register_get_info (reg);

    if (info->tcredit_str)
        return info->tcredit_str;

    {
        const char *string = gnc_split_register_get_credit_string (reg);

        if (string)
            info->tcredit_str = g_strdup_printf (_("Tot %s"), string);
    }

    if (info->tcredit_str)
        return info->tcredit_str;

    info->tcredit_str = g_strdup (_("Tot Credit"));

    return info->tcredit_str;
}
