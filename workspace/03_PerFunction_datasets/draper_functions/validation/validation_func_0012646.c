x11_context_modes_create(unsigned count)
{
   const size_t size = sizeof(__GLcontextModes);
   __GLcontextModes *base = NULL;
   __GLcontextModes **next;
   unsigned i;

   next = &base;
   for (i = 0; i < count; i++) {
      *next = (__GLcontextModes *) CALLOC(1, size);
      if (*next == NULL) {
         x11_context_modes_destroy(base);
         base = NULL;
         break;
      }
      next = &((*next)->next);
   }

   return base;
}
