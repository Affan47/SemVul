cleanword(char * dest, const char * src,
    int * pcaptype, int * pabbrev)
{
   unsigned char * p = (unsigned char *) dest;
   const unsigned char * q = (const unsigned char * ) src;
   int firstcap = 0;


   while ((*q != '\0') && (*q == ' ')) q++;


   *pabbrev = 0;
   int nl = strlen((const char *)q);
   while ((nl > 0) && (*(q+nl-1)=='.')) {
       nl--;
       (*pabbrev)++;
   }


   if (nl <= 0) {
       *pcaptype = NOCAP;
       *p = '\0';
       return 0;
   }


   int ncap = 0;
   int nneutral = 0;
   int nc = 0;

   if (!utf8) {
      while (nl > 0) {
         nc++;
         if (csconv[(*q)].ccase) ncap++;
         if (csconv[(*q)].cupper == csconv[(*q)].clower) nneutral++;
         *p++ = *q++;
         nl--;
      }

      *p = '\0';
      firstcap = csconv[(unsigned char)(*dest)].ccase;
   } else {
      unsigned short idx;
      w_char t[MAXWORDLEN];
      nc = u8_u16(t, MAXWORDLEN, src);
      for (int i = 0; i < nc; i++) {
         idx = (t[i].h << 8) + t[i].l;
         unsigned short low = unicodetolower(idx, langnum);
         if (idx != low) ncap++;
         if (unicodetoupper(idx, langnum) == low) nneutral++;
      }
      u16_u8(dest, MAXWORDUTF8LEN, t, nc);
      if (ncap) {
         idx = (t[0].h << 8) + t[0].l;
         firstcap = (idx != unicodetolower(idx, langnum));
      }
   }


   if (ncap == 0) {
        *pcaptype = NOCAP;
   } else if ((ncap == 1) && firstcap) {
        *pcaptype = INITCAP;
   } else if ((ncap == nc) || ((ncap + nneutral) == nc)){
        *pcaptype = ALLCAP;
   } else if ((ncap > 1) && firstcap) {
        *pcaptype = HUHINITCAP;
   } else {
        *pcaptype = HUHCAP;
   }
   return strlen(dest);
}
