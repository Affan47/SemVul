glXQueryRendererStringMESA(Display *dpy, int screen,
                           int renderer, int attribute)
{
   struct glx_screen *psc;

   if (dpy == NULL)
      return False;


   psc = GetGLXScreenConfigs(dpy, screen);
   if (psc == NULL)
      return False;


   if (renderer != 0)
      return False;

   return __glXQueryRendererString(psc, attribute);
}
