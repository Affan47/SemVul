gma_transform(const GRect & grect)
{
   int width=get_xmax()-get_xmin();
   int height=get_ymax()-get_ymin();
   int xmin=get_xmin(), ymin=get_ymin();
   for(int i=0;i<points;i++)
   {
      xx[i]=grect.xmin+(xx[i]-xmin)*grect.width()/width;
      yy[i]=grect.ymin+(yy[i]-ymin)*grect.height()/height;
   }
}
