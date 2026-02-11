e_border_maximize(E_Border *bd,
                  E_Maximize max)
{
   E_OBJECT_CHECK(bd);
   E_OBJECT_TYPE_CHECK(bd, E_BORDER_TYPE);

   if (!(max & E_MAXIMIZE_DIRECTION)) max |= E_MAXIMIZE_BOTH;

   if ((bd->shaded) || (bd->shading)) return;
   ecore_x_window_shadow_tree_flush();
   if (bd->fullscreen)
     e_border_unfullscreen(bd);

   if (((bd->maximized & E_MAXIMIZE_DIRECTION) == (max & E_MAXIMIZE_DIRECTION)) ||
       ((bd->maximized & E_MAXIMIZE_DIRECTION) == E_MAXIMIZE_BOTH)) return;
   if (bd->new_client)
     {
        bd->need_maximize = 1;
        bd->maximized &= ~E_MAXIMIZE_TYPE;
        bd->maximized |= max;
        return;
     }

   bd->pre_res_change.valid = 0;
   if (!(bd->maximized & E_MAXIMIZE_HORIZONTAL))
     {

        bd->saved.x = bd->x - bd->zone->x;
        bd->saved.w = bd->w;
     }
   if (!(bd->maximized & E_MAXIMIZE_VERTICAL))
     {

        bd->saved.y = bd->y - bd->zone->y;
        bd->saved.h = bd->h;
     }

   bd->saved.zone = bd->zone->num;
   e_hints_window_size_set(bd);

   e_border_raise(bd);

   _e_border_maximize(bd, max);


   bd->maximized &= ~E_MAXIMIZE_TYPE;

   bd->maximized |= max;

   if ((bd->maximized & E_MAXIMIZE_DIRECTION) > E_MAXIMIZE_BOTH)

     e_hints_window_maximized_set(bd, 0,
                                  ((bd->maximized & E_MAXIMIZE_DIRECTION) == E_MAXIMIZE_LEFT) ||
                                  ((bd->maximized & E_MAXIMIZE_DIRECTION) == E_MAXIMIZE_RIGHT));
   else
     e_hints_window_maximized_set(bd, bd->maximized & E_MAXIMIZE_HORIZONTAL,
                                  bd->maximized & E_MAXIMIZE_VERTICAL);
   e_remember_update(bd);
}
