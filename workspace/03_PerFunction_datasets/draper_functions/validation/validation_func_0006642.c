do_box(FILE *fp)
{
  int x1, y1, x2, y2, width, height;
  unsigned int color;
  struct LineStyle linestyle;
  struct FillStyle fillstyle;


  reset_attributes();


  if(fscanf(fp, "%d %d %d %d\n", &x1, &y1, &x2, &y2) != 4)
    {
      fprintf(stderr, "Error: Invalid box record #%d in %s()\n",
	      records_processed, __func__);
      exit(1);
    }

  x1 *= scale;
  y1 *= scale;
  x2 *= scale;
  y2 *= scale;

  width = x2-x1;
  height = y2-y1;
  color  = GRAPHIC_COLOR;

  linestyle = LINE_DEFAULT;
  fillstyle = FILL_DEFAULT;
  get_style(fp, &color, &linestyle, &fillstyle);

  box_object(x1,y1,width,height,color,&linestyle,&fillstyle);
}
