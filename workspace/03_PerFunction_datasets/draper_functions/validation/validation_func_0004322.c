reduce(
   const PermGroup *const G,
   const Unsigned level,
   Unsigned *const jPtr,
   WordImagePair *const whPtr)
{
   Unsigned i, j, pt;
   register Unsigned *temp1, *temp2;
   Unsigned *temp3, *temp4, *image;

   for ( j = level+1 ; j <= G->baseSize ; ++j ) {
      pt = whPtr->image[G->base[j]];
      if ( !G->schreierVec[j][pt] ) {
         *jPtr = j;
         return FALSE;
      }
      for ( ; pt != G->base[j] ;
              pt = G->schreierVec[j][pt]->invImage[pt] & NHB) {
         whPtr->word.position[++whPtr->word.length] =
                            G->schreierVec[j][pt]->invPermutation;
         image = whPtr->word.position[whPtr->word.length]->image;
         for ( i = 1 ; i <= G->degree ; ++i )
            whPtr->image[i] = image[whPtr->image[i]] & NHB;
      }
   }

   *jPtr = G->baseSize + 1;
   for ( pt = 1 ; pt <= G->degree ; ++pt )
      if ( whPtr->image[pt] != pt )
         return FALSE;

   return TRUE;
}
