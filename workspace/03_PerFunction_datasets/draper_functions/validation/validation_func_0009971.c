permutations(befig_list* befig)
{
   chain_list* port=NULL;
   chain_list* groupchain=NULL;
   bepor_list* bepor;
   biabl_list* biabl;


   if (befig->BEBUS) {
      for (biabl = befig->BEBUS->BIABL; biabl; biabl = biabl->NEXT )
      {
         groupchain=permute_variable(groupchain,biabl->CNDABL);
         groupchain=permute_variable(groupchain,biabl->VALABL);
      }
   }
   else if (befig->BEREG) {
      for (biabl = befig->BEREG->BIABL; biabl; biabl = biabl->NEXT )
      {
         groupchain=permute_variable(groupchain,biabl->CNDABL);
         groupchain=permute_variable(groupchain,biabl->VALABL);
      }
   }
   else if (befig->BEOUT) {
      groupchain=permute_variable(NULL,befig->BEOUT->ABL);
   }


   for (bepor=befig->BEPOR; bepor; bepor=bepor->NEXT) {
      port=addchain(port,bepor->NAME);
   }

   port=reverse(port);


   return compose(port, groupchain);
}
