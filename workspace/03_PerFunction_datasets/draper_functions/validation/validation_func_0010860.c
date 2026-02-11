driCopySubBuffer(__GLXDRIdrawable * pdraw,
                 int x, int y, int width, int height, Bool flush)
{
   struct dri_drawable *pdp = (struct dri_drawable *) pdraw;
   struct dri_screen *psc = (struct dri_screen *) pdp->base.psc;

   if (flush) {
      glFlush();
   }

   (*psc->driCopySubBuffer->copySubBuffer) (pdp->driDrawable,
					    x, y, width, height);
}
