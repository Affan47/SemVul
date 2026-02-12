char *GmfReadByteFlow(int64_t MshIdx, int *NmbByt)
{
   int         cod, *WrdTab;
   size_t      i, NmbWrd;
   GmfMshSct   *msh = (GmfMshSct *)MshIdx;


   if(!(NmbWrd = GmfStatKwd(MshIdx, GmfByteFlow)))
      return(NULL);

   if(!(WrdTab = malloc(NmbWrd * WrdSiz)))
      return(NULL);


   cod = msh->cod;
   msh->cod = 1;


   GmfGotoKwd(MshIdx, GmfByteFlow);
   GmfGetLin(MshIdx, GmfByteFlow, NmbByt);


   for(i=0;i<NmbWrd;i++)
      GmfGetLin(MshIdx, GmfByteFlow, &WrdTab[i]);


   msh->cod = cod;

   return((char *)WrdTab);
}
