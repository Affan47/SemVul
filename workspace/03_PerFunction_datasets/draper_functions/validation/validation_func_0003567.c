constructed (GObject *object)
{
  TpBaseConnection *base = TP_BASE_CONNECTION (object);
  void (*parent_impl) (GObject *) =
    G_OBJECT_CLASS (tp_tests_contacts_connection_parent_class)->constructed;

  if (parent_impl != NULL)
    parent_impl (object);

  tp_contacts_mixin_init (object,
      G_STRUCT_OFFSET (TpTestsContactsConnection, contacts_mixin));
  tp_base_connection_register_with_contacts_mixin (base);
  tp_contacts_mixin_add_contact_attributes_iface (object,
      TP_IFACE_CONNECTION_INTERFACE_ALIASING,
      aliasing_fill_contact_attributes);
  tp_contacts_mixin_add_contact_attributes_iface (object,
      TP_IFACE_CONNECTION_INTERFACE_AVATARS,
      avatars_fill_contact_attributes);
  tp_contacts_mixin_add_contact_attributes_iface (object,
      TP_IFACE_CONNECTION_INTERFACE_LOCATION,
      location_fill_contact_attributes);
  tp_contacts_mixin_add_contact_attributes_iface (object,
      TP_IFACE_CONNECTION_INTERFACE_CONTACT_CAPABILITIES,
      contact_caps_fill_contact_attributes);
  tp_contacts_mixin_add_contact_attributes_iface (object,
      TP_IFACE_CONNECTION_INTERFACE_CONTACT_INFO,
      contact_info_fill_contact_attributes);

  tp_presence_mixin_init (object,
      G_STRUCT_OFFSET (TpTestsContactsConnection, presence_mixin));
  tp_presence_mixin_simple_presence_register_with_contacts_mixin (object);
}
