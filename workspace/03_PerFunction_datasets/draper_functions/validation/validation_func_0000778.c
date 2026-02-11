_notification_popup_place(Popup_Data *popup,
                          int         pos)
{
   int w, h, sw, sh;
   int gap = 10;
   int to_edge = 15;

   sw = popup->zone->w;
   sh = popup->zone->h;
   evas_object_geometry_get(popup->theme, NULL, NULL, &w, &h);


   switch (notification_cfg->corner)
     {
      case CORNER_TL:
        e_popup_move(popup->win,
                     to_edge, to_edge + pos);
        break;
      case CORNER_TR:
        e_popup_move(popup->win,
                     sw - (w + to_edge),
                     to_edge + pos);
        break;
      case CORNER_BL:
        e_popup_move(popup->win,
                     to_edge,
                     (sh - h) - (to_edge + pos));
        break;
      case CORNER_BR:
        e_popup_move(popup->win,
                     sw - (w + to_edge),
                     (sh - h) - (to_edge + pos));
        break;
      default:
        break;
     }
   return pos + h + gap;
}
