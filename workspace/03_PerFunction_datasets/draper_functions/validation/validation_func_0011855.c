delete_ineffective_cuts(cut_pool *cp)
{
   cp_cut_data **cuts = cp->cuts;
   int num;
   int del_cuts = 0, tmp_del_cuts = 0, cuts_to_leave = 0;
   cp_cut_data **cp_cut1, **cp_cut2;
   int touches_until_deletion = cp->par.touches_until_deletion;
   int min_to_delete = cp->par.min_to_delete;

   if (min_to_delete > cp->cut_num)
      min_to_delete = (int)(0.2*cp->cut_num);

   switch (cp->par.delete_which){

    case DELETE_BY_QUALITY:

      order_cuts_by_quality(cp);

      cuts_to_leave = MIN(cp->par.cuts_to_check, cp->cut_num-min_to_delete);

      for (cp_cut1 = cuts + cuts_to_leave, num = cuts_to_leave;
	   num < cp->cut_num; cp_cut1++, num++){
	 del_cuts++;
	 cp->size -= (*cp_cut1)->cut.size;
	 FREE((*cp_cut1)->cut.coef);
	 FREE(*cp_cut1);
      }
      cp->cut_num -= del_cuts;
      cp->size -= del_cuts * (int) sizeof(cp_cut_data);
      break;

    case DELETE_BY_TOUCHES:
    default:

      while (del_cuts < min_to_delete){
	 for (tmp_del_cuts = 0, cp_cut1 = cp_cut2 = cuts,
		 num = cp->cut_num; num > 0; cp_cut2++, num--){
	    if ((*cp_cut2)->touches >= touches_until_deletion){
	       tmp_del_cuts++;
	       cp->size -= (*cp_cut2)->cut.size;
	       FREE((*cp_cut2)->cut.coef);
	       FREE(*cp_cut2);
	    }else{
	       *cp_cut1 = *cp_cut2;
	       cp_cut1++;
	    }
	 }
	 cp->cut_num -= tmp_del_cuts;
	 cp->size -= tmp_del_cuts * (int)sizeof(cp_cut_data);
	 del_cuts += tmp_del_cuts;
	 touches_until_deletion--;
      }
      break;

   }

   if (cp->par.verbosity > 5)
      printf("******* CUT_POOL : Deleted %i ineffective cuts leaving %i\n",
	     del_cuts, cp->cut_num);

   return(del_cuts);
}
