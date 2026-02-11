mcxStrNDup
(  const char* str
,  dim n
)
   {  char* rts = mcxAlloc(n+1, RETURN_ON_FAIL)
   ;  if (rts)
         memcpy(rts, str, n)
      ,  rts[n] = '\0'
   ;  return rts
;  }
