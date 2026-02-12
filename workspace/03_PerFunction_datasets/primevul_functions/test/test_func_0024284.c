int GmfWriteByteFlow(int64_t MshIdx, char *BytTab, int NmbByt)
{
   int i, PadWrd = 0, *WrdTab = (int *)BytTab, NmbWrd = NmbByt / WrdSiz;


   if(NmbByt > NmbWrd * 4)
      PadWrd = 1;


   if(!GmfSetKwd(MshIdx, GmfByteFlow, NmbWrd + PadWrd))
      return(0);


   GmfSetLin(MshIdx, GmfByteFlow, NmbByt);


   for(i=0;i<NmbWrd;i++)
      GmfSetLin(MshIdx, GmfByteFlow, WrdTab[i]);


   if(PadWrd)
   {
      PadWrd = 0;


      for(i=0; i<NmbByt - NmbWrd * 4; i++)
         PadWrd |= BytTab[ NmbWrd * 4 + i ] << (i*8);


      GmfSetLin(MshIdx, GmfByteFlow, PadWrd);
   }

   return(1);
}
