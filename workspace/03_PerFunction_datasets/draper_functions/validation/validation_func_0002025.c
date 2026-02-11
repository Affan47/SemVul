set_api_state(api_data *api)
{
   const Eina_List *disks = elm_box_children_get(api->box);
   if (!eina_list_count(disks))
     return;

   switch(api->state)
     {
      case SCROLLER_POLICY_SET_ON:
           {
              Evas_Object *disk = eina_list_nth(disks, 0);
              elm_scroller_policy_set(disk, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);
           }
         break;

      case SCROLLER_POLICY_SET_OFF:
           {
              Evas_Object *disk = eina_list_nth(disks, 0);
              elm_scroller_policy_set(disk, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
           }
         break;

      case BOUNCE_SET:
           {
              Evas_Object *disk = eina_list_nth(disks, 1);
              elm_scroller_bounce_set(disk, EINA_FALSE, EINA_FALSE);
           }
         break;

      case ITEM_LABEL_SET:
         elm_object_item_text_set(elm_diskselector_selected_item_get(eina_list_nth(disks, 0)), "Label from API");
         break;

      case TOOLTIP_TEXT_SET:
         elm_object_item_tooltip_text_set(elm_diskselector_selected_item_get(eina_list_nth(disks, 0)), "Tooltip from API");
         break;

      case ITEM_TOOLTIP_UNSET:
         elm_object_item_tooltip_unset(elm_diskselector_selected_item_get(eina_list_nth(disks, 0)));
         break;

      case ITEM_CURSOR_SET:
         elm_object_item_cursor_set(elm_diskselector_selected_item_get(eina_list_nth(disks, 0)), ELM_CURSOR_HAND2);
         break;

      case ITEM_CURSOR_UNSET:
         elm_object_item_cursor_unset(elm_diskselector_selected_item_get(eina_list_nth(disks, 0)));
         break;

      case ITEM_ICON_SET:
           {
              char buf[PATH_MAX];
              Evas_Object *ic = elm_icon_add(elm_object_parent_widget_get(eina_list_nth(disks, 0)));
              snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
              elm_image_file_set(ic, buf, NULL);
              elm_object_item_part_content_set(elm_diskselector_selected_item_get(eina_list_nth(disks, 0)), NULL, ic);
              evas_object_show(ic);
           }
         break;

      case SELECTED_SET:
           {
              elm_diskselector_item_selected_set(elm_diskselector_last_item_get(eina_list_nth(disks, 1)), EINA_TRUE);
              elm_diskselector_item_selected_set(elm_diskselector_item_next_get(elm_diskselector_selected_item_get(eina_list_nth(disks, 2))), EINA_TRUE);
           }
         break;

      case ITEM_PREV_GET:
           {
              elm_diskselector_item_selected_set(elm_diskselector_item_prev_get(elm_diskselector_selected_item_get(eina_list_nth(disks, 2))), EINA_TRUE);
           }
         break;

      case ITEM_DEL_NOT_SELECTED:
           {
              elm_object_item_del(elm_diskselector_item_prev_get(elm_diskselector_selected_item_get(eina_list_nth(disks, 2))));
           }
         break;

      case ITEM_DEL:
           {
              elm_object_item_del(elm_diskselector_selected_item_get(eina_list_nth(disks, 1)));
           }
         break;

      case CLEAR:
         elm_diskselector_clear(eina_list_nth(disks, 0));
         break;

      default:
         return;
     }
}
