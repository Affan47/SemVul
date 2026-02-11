used_inputs(befig_list* befig)
{
   bepor_list* bepor;
   bereg_list *bereg;
   beaux_list *beaux;
   bebus_list *bebus;
   bebux_list *bebux;
   beout_list *beout;
   biabl_list *biabl;


   for (bepor=befig->BEPOR; bepor; bepor=bepor->NEXT) {

      if (bepor->DIRECTION!=IN && bepor->DIRECTION!=INOUT
       && bepor->DIRECTION!=TRANSCV) continue;
      if (!isvdd(bepor->NAME) && !isvss(bepor->NAME)) {

         for ( beout = befig->BEOUT; beout; beout = beout->NEXT )
         {
            if ( is_input_used(bepor->NAME, beout->ABL) ) break;
         }
         if ( beout ) continue;

         for ( beaux = befig->BEAUX; beaux; beaux = beaux->NEXT )
         {
            if ( is_input_used(bepor->NAME, beaux->ABL) ) break;
         }
         if ( beaux ) continue;

         for ( bebux = befig->BEBUX; bebux; bebux = bebux->NEXT )
         {
            for ( biabl = bebux->BIABL; biabl; biabl = biabl->NEXT )
            {
               if ( is_input_used(bepor->NAME, biabl->CNDABL) ) break;
               if ( is_input_used(bepor->NAME, biabl->VALABL) ) break;
            }
            if ( biabl ) break;
         }
         if ( bebux ) continue;

         for ( bereg = befig->BEREG; bereg; bereg = bereg->NEXT )
         {
            for ( biabl = bereg->BIABL; biabl; biabl = biabl->NEXT )
            {
               if ( is_input_used(bepor->NAME, biabl->CNDABL) ) break;
               if ( is_input_used(bepor->NAME, biabl->VALABL) ) break;
            }
            if ( biabl ) break;
         }
         if ( bereg ) continue;

         for ( bebus = befig->BEBUS; bebus; bebus = bebus->NEXT )
         {
            for ( biabl = bebus->BIABL; biabl; biabl = biabl->NEXT )
            {
               if ( is_input_used(bepor->NAME, biabl->CNDABL) ) break;
               if ( is_input_used(bepor->NAME, biabl->VALABL) ) break;
            }
            if ( biabl ) break;
         }
         if ( bebus ) continue;

         fprintf(stderr,"BEH: %s input unused\n",bepor->NAME);
         return 0;

      }
   }

   return 1;
}
