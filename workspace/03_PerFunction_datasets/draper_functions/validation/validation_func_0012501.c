lStr2NmGenerator(const char *str, lNameSpace *ns)
{
   const lNameSpace *nsp;
   int ret;

   DENTER(CULL_LAYER, "lStr2NmGenerator");

   for (nsp = ns; nsp->lower; nsp++) {
      if ((ret = _lStr2Nm(nsp, str)) != NoName) {
         DPRINTF(("Name: %s Id: %d\n", str, ret));
         DEXIT;
         return ret;
      }
   }

   DEXIT;
   return NoName;
}
