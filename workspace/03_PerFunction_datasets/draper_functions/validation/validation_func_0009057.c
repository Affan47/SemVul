mrg_store(source, dest)
struct store *source;
struct store *dest;
   {
   int i;

   if (source == NULL)
      return;


   if (dest->perm) {
      for (i = 0; i < n_gbl + n_loc; ++i)
         ChkMrgTyp(n_icntyp, source->types[i], dest->types[i])
      }
   else {
      for (i = 0; i < n_gbl + n_loc; ++i)
         MrgTyp(n_icntyp, source->types[i], dest->types[i])
      }
   }
