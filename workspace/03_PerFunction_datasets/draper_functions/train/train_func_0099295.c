e_container_shape_geometry_get(E_Container_Shape *es, int *x, int *y, int *w, int *h)
{
   E_OBJECT_CHECK(es);
   E_OBJECT_TYPE_CHECK(es, E_CONTAINER_SHAPE_TYPE);
   if (x) *x = es->x;
   if (y) *y = es->y;
   if (w) *w = es->w;
   if (h) *h = es->h;
}
