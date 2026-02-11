SLHLHook(uint8 *bg, uint8 *spr, uint32 linets, int final)
{
 int x;

 for(x=0;x<2;x++)
  if(JPorts[x]->SLHook)
   JPorts[x]->SLHook(x,bg,spr,linets,final);
 if(FCExp)
  if(FCExp->SLHook)
   FCExp->SLHook(bg,spr,linets,final);
}
