e_gadcon_zone_get(E_Gadcon *gc)
{
   E_OBJECT_CHECK_RETURN(gc, NULL);
   E_OBJECT_TYPE_CHECK_RETURN(gc, E_GADCON_TYPE, NULL);
   if (gc->zone) return gc->zone;
   if (!gc->toolbar) return NULL;
   return gc->toolbar->fwin->border->zone;
}
