mcxFNVhash
(  const void *buf
,  u32 len
)
   {  u32 hval = 0x811c9dc5
   ;  const char *bp = buf

   ;  while (len--)
      {
#if 0
         hval *= 0x01000193
#else
         hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24)
#endif
      ;  hval ^= *bp++;
   ;  }
       return hval
;  }
