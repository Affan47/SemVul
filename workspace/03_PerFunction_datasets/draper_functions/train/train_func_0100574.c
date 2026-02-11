e_modapi_init(E_Module *m)
{
   conf_item_edd = E_CONFIG_DD_NEW("IBox_Config_Item", Config_Item);
   #undef T
   #undef D
   #define T Config_Item
   #define D conf_item_edd
   E_CONFIG_VAL(D, T, id, STR);
   E_CONFIG_VAL(D, T, expand_on_desktop, INT);
   E_CONFIG_VAL(D, T, show_label, INT);
   E_CONFIG_VAL(D, T, show_zone, INT);
   E_CONFIG_VAL(D, T, show_desk, INT);
   E_CONFIG_VAL(D, T, icon_label, INT);

   conf_edd = E_CONFIG_DD_NEW("IBox_Config", Config);
   #undef T
   #undef D
   #define T Config
   #define D conf_edd
   E_CONFIG_LIST(D, T, items, conf_item_edd);

   ibox_config = e_config_domain_load("module.ibox", conf_edd);
   if (!ibox_config)
     {
        Config_Item *ci;

        ibox_config = E_NEW(Config, 1);

        ci = E_NEW(Config_Item, 1);
        ci->id = eina_stringshare_add("ibox.1");
        ci->show_label = 0;
        ci->show_zone = 1;
        ci->show_desk = 0;
        ci->icon_label = 0;
        ibox_config->items = eina_list_append(ibox_config->items, ci);
     }

   ibox_config->module = m;

   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_ADD, _ibox_cb_event_border_add, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_REMOVE, _ibox_cb_event_border_remove, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_ICONIFY, _ibox_cb_event_border_iconify, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_UNICONIFY, _ibox_cb_event_border_uniconify, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_ICON_CHANGE, _ibox_cb_event_border_icon_change, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_URGENT_CHANGE, _ibox_cb_event_border_urgent_change, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_BORDER_ZONE_SET, _ibox_cb_event_border_zone_set, NULL);
   E_LIST_HANDLER_APPEND(ibox_config->handlers, E_EVENT_DESK_SHOW, _ibox_cb_event_desk_show, NULL);


   e_gadcon_provider_register(&_gadcon_class);
   return m;
}
