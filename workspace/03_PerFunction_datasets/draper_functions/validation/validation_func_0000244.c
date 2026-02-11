publish (G_GNUC_UNUSED const Ekiga::PersonalDetails& details_)
{
  if (group != NULL) {

    Ekiga::CallManager::InterfaceList interfaces;
    AvahiStringList* txt_record = NULL;

    txt_record = prepare_txt_record ();
    for (Ekiga::CallCore::const_iterator iter = call_core.begin ();
	 iter != call_core.end ();
	 ++iter) {

      Ekiga::CallManager::InterfaceList ints = (*iter)->get_interfaces ();
      interfaces.insert (interfaces.begin (), ints.begin (), ints.end ());

    }

    for (Ekiga::CallManager::InterfaceList::const_iterator iter = interfaces.begin ();
	 iter != interfaces.end ();
	 ++iter) {

      gchar *typ = NULL;

      typ = g_strdup_printf ("_%s._%s",
			     iter->voip_protocol.c_str (),
			     iter->protocol.c_str ());


      avahi_entry_group_update_service_txt_strlst (group, AVAHI_IF_UNSPEC,
						   AVAHI_PROTO_UNSPEC,
						   (AvahiPublishFlags)0,
						   name, typ, NULL,
						   txt_record);

      g_free (typ);
    }

    avahi_string_list_free (txt_record);
  }
}
