update_label(struct Service *s, const gchar *hostname, const AvahiAddress *a, guint16 port, AvahiStringList *txt) {
    gchar t[512], address[64], *txt_s;
    char name[IF_NAMESIZE];

    if (a && hostname) {
        char na[AVAHI_ADDRESS_STR_MAX];
        avahi_address_snprint(na, sizeof(na), a);
        snprintf(address, sizeof(address), "%s/%s:%u", hostname, na, port);

        if (txt)
            txt_s = avahi_string_list_to_string(txt);
        else
            txt_s = g_strdup("<i>empty</i>");
    } else {
        snprintf(address, sizeof(address), "<i>n/a</i>");
        txt_s = g_strdup("<i>n/a</i>");
    }

    snprintf(t, sizeof(t),
             "<b>Service Type:</b> %s\n"
             "<b>Service Name:</b> %s\n"
             "<b>Domain Name:</b> %s\n"
             "<b>Interface:</b> %s %s\n"
             "<b>Address:</b> %s\n"
             "<b>TXT Data:</b> %s",
             s->service_type->service_type,
             s->service_name,
             s->domain_name,
             if_indextoname(s->interface,name), avahi_proto_to_string(s->protocol),
             address,
             txt_s);

    gtk_label_set_markup(info_label, t);

    g_free(txt_s);
}
