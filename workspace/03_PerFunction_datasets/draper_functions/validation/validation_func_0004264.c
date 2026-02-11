settings_gui_shutdown(void)
{
    guint n;


    for (n = 0; n < G_N_ELEMENTS(property_map); n ++) {
        if (property_map[n].cb != IGNORE_CB) {
            property_map[n].stub->prop_changed_listener.remove(
                property_map[n].prop,
                property_map[n].cb);
        }
    }

	hikset_foreach(sensitive_changes, sensitive_free_value, NULL);
	hikset_free_null(&sensitive_changes);


	settings_gui_save_panes();


    prop_save_to_file(properties, settings_gui_config_dir(), property_file);


    gui_prop_shutdown();

    G_FREE_NULL(home_dir);
}
