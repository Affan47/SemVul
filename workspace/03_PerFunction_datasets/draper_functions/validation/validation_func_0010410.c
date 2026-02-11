toggleswitch(pbutton      pb)
{

   char *pbl = (char*) pb->data;

   if ( pb->style == 10 )
      *pbl = 1;
   else
      *pbl = ! *pbl;


   int col;

   if (*pbl)
      col = pb->min;
   else
      col = pb->max;

   line(x1 + pb->x1,y1 + pb->y1,x1 + pb->x1 + (pb->y2 - pb->y1),y1 + pb->y2, col);
   line(x1 + pb->x1 + (pb->y2 - pb->y1),y1 + pb->y1,x1 + pb->x1,y1 + pb->y2, col);

   buttonpressed(pb->id);

}
