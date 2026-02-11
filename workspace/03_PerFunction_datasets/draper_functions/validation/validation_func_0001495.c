gwy_volume_func_get_sensitivity_mask(const gchar *name)
{
    GwyVolumeFuncInfo *func_info;

    func_info = g_hash_table_lookup(volume_funcs, name);
    g_return_val_if_fail(func_info, 0);

    return func_info->sens_mask;
}
