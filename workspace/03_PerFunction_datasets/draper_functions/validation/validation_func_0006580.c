efreet_desktop_init(void)
{
    _efreet_desktop_log_dom = eina_log_domain_register
      ("efreet_desktop", EFREET_DEFAULT_LOG_COLOR);
    if (_efreet_desktop_log_dom < 0)
    {
        EINA_LOG_ERR("Efreet: Could not create a log domain for efreet_desktop");
        return 0;
    }

#ifdef HAVE_EVIL
    if (!evil_sockets_init())
      {
         ERR("Could not initialize Winsock system");
         return 0;
      }
#endif

    efreet_desktop_types = NULL;

    EFREET_DESKTOP_TYPE_APPLICATION = efreet_desktop_type_add("Application",
                                        efreet_desktop_application_fields_parse,
                                        efreet_desktop_application_fields_save,
                                        NULL);
    EFREET_DESKTOP_TYPE_LINK = efreet_desktop_type_add("Link",
                                    efreet_desktop_link_fields_parse,
                                    efreet_desktop_link_fields_save, NULL);
    EFREET_DESKTOP_TYPE_DIRECTORY = efreet_desktop_type_add("Directory", NULL,
                                                                NULL, NULL);

    efreet_desktop_changes_listen();
    return 1;
}
