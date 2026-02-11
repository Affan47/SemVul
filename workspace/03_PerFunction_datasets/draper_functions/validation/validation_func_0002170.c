match_3rd_pair(unsigned char p1, unsigned char p2,
                   int *possible, int *nposs)
{
   int i;
   int tnposs;


   tnposs = *nposs;

   *nposs = 0;


   for(i = 0; i < tnposs; i++){

      if((p1==g_feature_patterns[possible[i]].third[0]) &&
         (p2==g_feature_patterns[possible[i]].third[1])){

         possible[*nposs] = possible[i];

         (*nposs)++;
      }
   }


   return(*nposs);
}
