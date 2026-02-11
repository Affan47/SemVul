make_font_chooser(void)
{
  int font_idx;


  create_font_widget();


#ifdef WIN32
  font_count = Fl::set_fonts("*");
#elif __APPLE__
  font_count = Fl::set_fonts("*");
#else


  font_count = Fl::set_fonts("-*-*-*-*-*-*-*-*-*-*-*-*-iso10646-1");
#endif


  sizes = new int*[font_count];
  numsizes = new int[font_count];


  first_free = FL_FREE_FONT;
  for (font_idx = first_free; font_idx < font_count; font_idx++)
  {

    int *size_array;
    int size_count = Fl::get_font_sizes((Fl_Font)font_idx, size_array);
    numsizes[font_idx-first_free] = size_count;

    if (size_count)
    {
      sizes[font_idx-first_free] = new int[size_count];
      for (int j = 0; j < size_count; j++)
        sizes[font_idx-first_free][j] = size_array[j];
    }
  }


  own_face_cb(NULL, 0);

  fontobj->value(1);


  font_cb(fontobj, 0);

  fnt_cnt->value(font_count);

  return font_count;

}
