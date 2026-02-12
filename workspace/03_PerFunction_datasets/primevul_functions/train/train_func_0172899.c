LBLIST *get_subgroup(LBLIST pgrp, char *logbook)

{
   int i;

   for (i = 0; i < pgrp->n_members; i++) {

      if (strieq(logbook, pgrp->member[i]->name))
         return &(pgrp->member[i]);


      if (pgrp->member[i]->n_members > 0 && get_subgroup(pgrp->member[i], logbook))
         return get_subgroup(pgrp->member[i], logbook);
   }

   return NULL;
}
