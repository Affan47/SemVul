dump_aout()
{
static char * cpu[] = { "unknown", "8086", "m68k", "ns16k", "i386", "sparc" };
static char * byteord[] = { "LITTLE_ENDIAN", "(2143)","(3412)","BIG_ENDIAN" };
   int i;
   long l;

   if( h_cpu > 0x17 ) h_cpu &= 3;

   printf("HLEN %d\n", h_len);
   printf("CPU  %s %s\n", cpu[h_cpu>>2], byteord[h_cpu&3]);

   printf("FLAGS:");
   if( h_flgs & 0x01 ) printf(" A_UZP");
   if( h_flgs & 0x02 ) printf(" A_PAL");
   if( h_flgs & 0x04 ) printf(" A_NSYM");
   if( h_flgs & 0x08 ) printf(" FLG-08");
   if( h_flgs & 0x10 ) printf(" A_EXEC");
   if( h_flgs & 0x20 ) printf(" A_SEP");
   if( h_flgs & 0x40 ) printf(" A_PURE");
   if( h_flgs & 0x80 ) printf(" A_TOVLY");
   printf("\n");

   if( header[5] )
      printf("a_entry  = 0x%08lx\n", header[5]);
   printf("a_total  = 0x%08lx\n", header[6]);
   if( header[7] )
      printf("a_syms   = 0x%08lx\n", header[7]);

   if( h_len >= 36 )
      printf("a_trsize = 0x%08lx\n", header[8]);
   if( h_len >= 40 )
      printf("a_drsize = 0x%08lx\n", header[9]);
   if( h_len >= 44 )
      printf("a_tbase  = 0x%08lx\n", header[10]);
   if( h_len >= 48 )
      printf("a_dbase  = 0x%08lx\n", header[11]);
   printf("\n");

   size_aout();
   printf("\n");

   if( header[7] )
   {
      printf("SYMBOLS\n");
      nm_aout();
   }
   else
      printf("NO SYMBOLS\n");
   printf("\n");

   printf("TEXTSEG\n");
   fseek(ifd, (long)h_len, 0);
   for(l=0; l<header[2]; l++)
   {
      if( (i=getc(ifd)) == EOF ) break;
      hex_output(i);
   }
   hex_output(EOF);

   printf("DATASEG\n");
   fseek(ifd, (long)h_len+header[2], 0);
   for(l=0; l<header[3]; l++)
   {
      if( (i=getc(ifd)) == EOF ) break;
      hex_output(i);
   }
   hex_output(EOF);
}
