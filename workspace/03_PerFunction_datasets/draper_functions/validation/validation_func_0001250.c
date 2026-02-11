main(int argc, char **argv)
{
    GVirConfigCapabilities *caps;
    GVirConfigCapabilitiesHost *host_caps;
    GList *guests_caps, *iter;
    char *xml;
    GError *error = NULL;

    gvir_config_init(&argc, &argv);
    if (argc != 2) {
        g_print("Usage: %s filename\n", argv[0]);
        g_print("Attempt to parse the libvirt XML definition from filename\n");
        return 1;
    }

    g_file_get_contents(argv[1], &xml, NULL, &error);
    if (error != NULL) {
        g_print("Couldn't read %s: %s\n", argv[1], error->message);
        return 2;
    }

    caps = gvir_config_capabilities_new_from_xml(xml, &error);
    g_free(xml);
    if (error != NULL) {
        g_print("Couldn't parse %s: %s\n", argv[1], error->message);
        return 3;
    }
    g_assert(caps != NULL);
    gvir_config_object_validate(GVIR_CONFIG_OBJECT(caps), &error);
    if (error != NULL) {
        g_print("%s format is invalid: %s\n", argv[1], error->message);
        g_clear_error(&error);
    }

    host_caps = gvir_config_capabilities_get_host(caps);
    verify_host_caps(host_caps);
    g_object_unref(G_OBJECT(host_caps));

    guests_caps = gvir_config_capabilities_get_guests(caps);
    for (iter = guests_caps; iter != NULL; iter = iter->next) {
        GVirConfigCapabilitiesGuest *guest_caps;

        guest_caps = GVIR_CONFIG_CAPABILITIES_GUEST(iter->data);
        verify_guest_caps(guest_caps);
        g_object_unref(G_OBJECT(guest_caps));
    }
    g_list_free(guests_caps);

    xml = gvir_config_object_to_xml(GVIR_CONFIG_OBJECT(caps));
    g_print("%s\n", xml);
    g_free(xml);
    g_object_unref(G_OBJECT(caps));

    return 0;
}
