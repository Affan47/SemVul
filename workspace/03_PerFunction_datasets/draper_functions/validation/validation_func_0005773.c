ArgusFindFlow ()
{
   struct ArgusFlowStruct *retn = NULL;
   struct ArgusHashTableHeader *hashEntry;
   unsigned short hash = 0, *ptr = (unsigned short *) ArgusThisFlow;
   int i, len;

   for (i = 0, len = (sizeof(*ArgusThisFlow)) / sizeof(unsigned short); i < len; i++)
      hash += *ptr++;

   ArgusThisHash = hash;
   if ((hashEntry = ArgusFindHashObject ()) != NULL)
      retn = hashEntry->flowobj;

#ifdef ARGUSDEBUG
   ArgusDebug (6, "ArgusFindFlow () returning 0x%x\n", retn);
#endif

   return (retn);
}
