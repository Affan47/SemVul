_map_mouse_down(void *data, Evas *evas __UNUSED__, Evas_Object *obj, void *event_info)
{
   Evas_Event_Mouse_Down *down = event_info;
   Elm_Object_Item *menu_it;
   if (!down) return;

   if (down->button == 2)
     {
        old_x = down->canvas.x;
        old_y = down->canvas.y;
        old_d = 0.0;
     }
   else if (down->button == 3)
     {
        down_x = down->canvas.x;
        down_y = down->canvas.y;
        menu = elm_menu_add(obj);
        menu_it = elm_menu_item_add(menu, NULL, "", "Source", NULL, NULL);
        _submenu_src_add(data, menu_it);
        menu_it = elm_menu_item_add(menu, NULL, "", "Move", NULL, NULL);
        _submenu_move_add(data, menu_it);
        menu_it = elm_menu_item_add(menu, NULL, "", "Zoom", NULL, NULL);
        _submenu_zoom_add(data, menu_it);
        menu_it = elm_menu_item_add(menu, NULL, "", "Prop", NULL, NULL);
        _submenu_prop_add(data, menu_it);
        menu_it = elm_menu_item_add(menu, NULL, "", "Track", NULL, NULL);
        _submenu_track_add(data, menu_it);
        menu_it = elm_menu_item_add(menu, NULL, "", "Overlay", NULL, NULL);
        _submenu_ovl_add(data, menu_it);

         elm_menu_move(menu, down->canvas.x, down->canvas.y);
         evas_object_show(menu);
     }
}
