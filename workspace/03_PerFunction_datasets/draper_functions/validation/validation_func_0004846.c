_e_zone_useful_geometry_calc(E_Zone *zone)
{
   const E_Shelf *shelf;
   Eina_List *shelves;
   int x0, x1, yy0, yy1;

   x0 = 0;
   yy0 = 0;
   x1 = zone->w;
   yy1 = zone->h;
   shelves = e_shelf_list_all();
   EINA_LIST_FREE(shelves, shelf)
     {
        E_Config_Shelf_Desk *sd;
        E_Gadcon_Orient orient;
        Eina_List *ll;
        int skip_shelf = 0;

        if (shelf->zone != zone)
          continue;

        if (shelf->cfg)
          {
             if (shelf->cfg->overlap)
               continue;

             if (shelf->cfg->autohide)
               continue;
             orient = shelf->cfg->orient;

             if (shelf->cfg->desk_show_mode)
               {
                  skip_shelf = 1;
                  EINA_LIST_FOREACH(shelf->cfg->desk_list, ll, sd)
                    {
                       if (!sd) continue;
                       if ((sd->x == zone->desk_x_current) && (sd->y == zone->desk_y_current))
                         {
                            skip_shelf = 0;
                            break;
                         }
                    }
                  if (skip_shelf)
                    continue;
               }
          }
        else
          orient = shelf->gadcon->orient;

        switch (orient)
          {

            case E_GADCON_ORIENT_FLOAT:
            case E_GADCON_ORIENT_HORIZ:
            case E_GADCON_ORIENT_VERT:
              break;

            case E_GADCON_ORIENT_TOP:
            case E_GADCON_ORIENT_CORNER_TL:
            case E_GADCON_ORIENT_CORNER_TR:
              if (yy0 < shelf->h)
                yy0 = shelf->h;
              break;

            case E_GADCON_ORIENT_BOTTOM:
            case E_GADCON_ORIENT_CORNER_BL:
            case E_GADCON_ORIENT_CORNER_BR:
              if (yy1 > zone->h - shelf->h)
                yy1 = zone->h - shelf->h;
              break;

            case E_GADCON_ORIENT_LEFT:
            case E_GADCON_ORIENT_CORNER_LT:
            case E_GADCON_ORIENT_CORNER_LB:
              if (x0 < shelf->w)
                x0 = shelf->w;
              break;

            case E_GADCON_ORIENT_RIGHT:
            case E_GADCON_ORIENT_CORNER_RT:
            case E_GADCON_ORIENT_CORNER_RB:
              if (x1 > zone->w - shelf->w)
                x1 = zone->w - shelf->w;
              break;
            default:
              break;
          }
     }

   zone->useful_geometry.x = zone->x + x0;
   zone->useful_geometry.y = zone->y + yy0;
   zone->useful_geometry.w = x1 - x0;
   zone->useful_geometry.h = yy1 - yy0;
   zone->useful_geometry.dirty = 0;
}
