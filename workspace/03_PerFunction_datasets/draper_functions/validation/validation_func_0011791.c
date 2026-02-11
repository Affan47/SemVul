gwy_app_update_last_process_func(const gchar *name)
{
    GtkWidget *repeat_item, *reshow_item, *label;
    GwySensitivityGroup *sensgroup;
    GwyMenuSensFlags sens;
    const gchar *menu_path;
    gchar *s, *lab;

    gwy_func_use_add(gwy_app_process_func_get_use(), name);

    if (!last_name_quark)
        last_name_quark = g_quark_from_static_string("gwy-app-menu-last"
                                                     "-func-name");

    g_return_if_fail(GTK_IS_MENU(process_menu));
    g_object_set_qdata(G_OBJECT(process_menu), last_name_quark, (gpointer)name);
    repeat_item = g_object_get_qdata(G_OBJECT(process_menu), repeat_last_quark);
    reshow_item = g_object_get_qdata(G_OBJECT(process_menu), reshow_last_quark);
    g_return_if_fail(repeat_item && reshow_item);


    menu_path = gettext(gwy_process_func_get_menu_path(name));
    menu_path = strrchr(menu_path, '/');
    g_assert(menu_path);
    menu_path++;
    lab = g_strdup(menu_path);
    gwy_app_menu_canonicalize_label(lab);
    sensgroup = gwy_app_sensitivity_get_group();
    sens = (gwy_process_func_get_sensitivity_mask(name)
            | GWY_MENU_FLAG_LAST_PROC);

    label = GTK_BIN(repeat_item)->child;
    s = g_strconcat(_("Repeat"), " (", lab, ")", NULL);
    gtk_label_set_text_with_mnemonic(GTK_LABEL(label), s);
    gwy_sensitivity_group_set_widget_mask(sensgroup, repeat_item, sens);
    g_free(s);

    label = GTK_BIN(reshow_item)->child;
    s = g_strconcat(_("Re-show"), " (", lab, ")", NULL);
    gtk_label_set_text_with_mnemonic(GTK_LABEL(label), s);
    gwy_sensitivity_group_set_widget_mask(sensgroup, reshow_item, sens);
    g_free(s);

    g_free(lab);
}
