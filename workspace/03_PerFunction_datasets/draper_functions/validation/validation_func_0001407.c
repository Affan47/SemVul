_e_shelf_bindings_add(E_Shelf *es)
{
   char buf[1024];


   _e_shelf_bindings_del(es);


   if ((es->cfg) && (!es->cfg->autohide) &&
       (!es->cfg->autohide_show_action))
     return;

   snprintf(buf, sizeof(buf), "shelf.%d", es->id);
   switch (es->gadcon->orient)
     {
      case E_GADCON_ORIENT_FLOAT:
      case E_GADCON_ORIENT_HORIZ:
      case E_GADCON_ORIENT_VERT:
      default:

        break;

      case E_GADCON_ORIENT_LEFT:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_LEFT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_RIGHT:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_RIGHT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_TOP:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_TOP,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_BOTTOM:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_BOTTOM,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_CORNER_TL:
      case E_GADCON_ORIENT_CORNER_LT:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_TOP,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_LEFT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_TOP_LEFT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_CORNER_TR:
      case E_GADCON_ORIENT_CORNER_RT:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_TOP,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_RIGHT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_TOP_RIGHT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_CORNER_BL:
      case E_GADCON_ORIENT_CORNER_LB:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_BOTTOM,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_LEFT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_BOTTOM_LEFT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;

      case E_GADCON_ORIENT_CORNER_BR:
      case E_GADCON_ORIENT_CORNER_RB:
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_BOTTOM,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_RIGHT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        e_bindings_edge_add(E_BINDING_CONTEXT_ZONE, E_ZONE_EDGE_BOTTOM_RIGHT,
                            E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
        break;
     }
}
