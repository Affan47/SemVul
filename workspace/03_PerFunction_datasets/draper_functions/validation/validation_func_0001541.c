FCEU_LoadGamePalette(void)
{
  uint8 ptmp[192];
  FILE *fp;
  char *fn;

  ipalette=0;

  fn=FCEU_MakeFName(FCEUMKF_PALETTE,0,0);

  if((fp=FCEUD_UTF8fopen(fn,"rb")))
  {
   int x;
   fread(ptmp,1,192,fp);
   fclose(fp);
   for(x=0;x<64;x++)
   {
    palettei[x].r=ptmp[x+x+x];
    palettei[x].g=ptmp[x+x+x+1];
    palettei[x].b=ptmp[x+x+x+2];
   }
   ipalette=1;
  }
  free(fn);
}
