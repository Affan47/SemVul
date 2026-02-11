dri_create_context(struct glx_screen *base,
		   struct glx_config *config_base,
		   struct glx_context *shareList, int renderType)
{
   struct dri_context *pcp, *pcp_shared;
   struct dri_screen *psc = (struct dri_screen *) base;
   drm_context_t hwContext;
   __DRIcontext *shared = NULL;
   __GLXDRIconfigPrivate *config = (__GLXDRIconfigPrivate *) config_base;

   if (!psc->base.driScreen)
      return NULL;


   if (!validate_renderType_against_config(config_base, renderType))
       return NULL;

   if (shareList) {


      if (shareList->vtable->destroy != dri_destroy_context) {
	 return NULL;
      }

      pcp_shared = (struct dri_context *) shareList;
      shared = pcp_shared->driContext;
   }

   pcp = calloc(1, sizeof *pcp);
   if (pcp == NULL)
      return NULL;

   if (!glx_context_init(&pcp->base, &psc->base, &config->base)) {
      free(pcp);
      return NULL;
   }

   pcp->base.renderType = renderType;

   if (!XF86DRICreateContextWithConfig(psc->base.dpy, psc->base.scr,
                                       config->base.visualID,
                                       &pcp->hwContextID, &hwContext)) {
      free(pcp);
      return NULL;
   }

   pcp->driContext =
      (*psc->legacy->createNewContext) (psc->driScreen,
                                        config->driConfig,
                                        renderType, shared, hwContext, pcp);
   if (pcp->driContext == NULL) {
      XF86DRIDestroyContext(psc->base.dpy, psc->base.scr, pcp->hwContextID);
      free(pcp);
      return NULL;
   }

   pcp->base.vtable = &dri_context_vtable;

   return &pcp->base;
}
