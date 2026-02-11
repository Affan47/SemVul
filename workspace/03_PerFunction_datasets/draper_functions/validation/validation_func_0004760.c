cut_ui_factory_builder_init (CutUIFactoryBuilder *builder)
{
    const gchar *dir;

    dir = g_getenv("CUT_UI_FACTORY_MODULE_DIR");
    if (!dir) {
#ifdef G_OS_WIN32
        if (!win32_ui_factory_module_dir)
            win32_ui_factory_module_dir =
                cut_win32_build_factory_module_dir_name("ui");
        dir = win32_ui_factory_module_dir;
#else
        dir = UI_FACTORY_MODULEDIR;
#endif
    }

    g_object_set(G_OBJECT(builder),
                 "module-dir", dir,
                 NULL);
}
