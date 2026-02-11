driCreateDisplay(Display * dpy)
{
   struct dri_display *pdpyp;
   int eventBase, errorBase;
   int major, minor, patch;

   if (!XF86DRIQueryExtension(dpy, &eventBase, &errorBase)) {
      return NULL;
   }

   if (!XF86DRIQueryVersion(dpy, &major, &minor, &patch)) {
      return NULL;
   }

   pdpyp = malloc(sizeof *pdpyp);
   if (!pdpyp) {
      return NULL;
   }

   pdpyp->driMajor = major;
   pdpyp->driMinor = minor;
   pdpyp->driPatch = patch;

   pdpyp->base.destroyDisplay = driDestroyDisplay;
   pdpyp->base.createScreen = driCreateScreen;

   return &pdpyp->base;
}
