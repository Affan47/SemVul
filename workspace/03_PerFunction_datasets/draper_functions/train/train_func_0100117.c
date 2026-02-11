ElfHash(char *key)

{ unsigned char *p = key;
  int len = strlen(key);
  unsigned h = 0, g;
  unsigned int hashtablesize = CF_HASHTABLESIZE;
  int i;

for ( i = 0; i < len; i++ )
   {
   h = ( h << 4 ) + p[i];
   g = h & 0xf0000000L;

   if ( g != 0 )
      {
      h ^= g >> 24;
      }

   h &= ~g;
   }

return (h & (hashtablesize-1));
}
