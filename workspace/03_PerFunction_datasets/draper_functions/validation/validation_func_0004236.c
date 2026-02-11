draw_image_mono(Fl_Draw_Image_Cb call, void *data, int ix, int iy, int iw, int ih, int D) {
  double x = ix, y = iy, w = iw, h = ih;

  fprintf(output,"save\n");
  int i,j,k;
  const char * interpol;
  if (lang_level_>1){
    if (interpolate_) interpol="true";
    else interpol="false";
    if (mask && lang_level_>2)
      fprintf(output, "%g %g %g %g %i %i %i %i %s GIM\n", x , y+h , w , -h , iw , ih, mx, my, interpol);
    else
      fprintf(output, "%g %g %g %g %i %i %s GII\n", x , y+h , w , -h , iw , ih, interpol);
  } else
    fprintf(output , "%g %g %g %g %i %i GI", x , y+h , w , -h , iw , ih);

  int LD=iw*D;
  uchar *rgbdata=new uchar[LD];
  uchar *curmask=mask;
  for (j=0; j<ih;j++){

    if (mask && lang_level_>2){
      for (k=0; k<my/ih;k++){
        for (i=0; i<((mx+7)/8);i++){
          if (!(i%40)) fprintf(output, "\n");
          fprintf(output, "%.2x",swap_byte(*curmask));
          curmask++;
        }
        fprintf(output,"\n");
      }
    }
    call(data,0,j,iw,rgbdata);
    uchar *curdata=rgbdata;
    for (i=0 ; i<iw ; i++) {
      uchar r = curdata[0];
      if (!(i%120)) fprintf(output, "\n");
      fprintf(output, "%.2x", r);
      curdata +=D;
    }
    fprintf(output,"\n");
  }
  fprintf(output,">\n");
  fprintf(output,"restore\n");
  delete[] rgbdata;
}
