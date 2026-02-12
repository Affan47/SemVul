static int cborElemNameToJson (OSCTXT* pCborCtxt, OSCTXT* pJsonCtxt)
{
   char* pElemName = 0;
   OSOCTET ub;
   int ret;


   ret = rtxReadBytes (pCborCtxt, &ub, 1);
   if (0 != ret) return LOG_RTERR (pCborCtxt, ret);


   ret = rtCborDecDynUTF8Str (pCborCtxt, ub, &pElemName);
   if (0 != ret) return LOG_RTERR (pCborCtxt, ret);


   ret = rtJsonEncStringValue (pJsonCtxt, (const OSUTF8CHAR*)pElemName);
   rtxMemFreePtr (pCborCtxt, pElemName);
   if (0 != ret) return LOG_RTERR (pJsonCtxt, ret);

   OSRTSAFEPUTCHAR (pJsonCtxt, ':');

   return 0;
}
