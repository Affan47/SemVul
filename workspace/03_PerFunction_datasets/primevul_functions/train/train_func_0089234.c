push_colours(uint ix)
{
  if (ix > 10)
    return;

  if (ix) {
    colours_cur = ix;
    ix--;
  }
  else {
    if (colours_cur < 10) {
      ix = colours_cur;
      colours_cur++;
    }
    else
      return;
  }


  if (!colours_stack[ix]) {
    colours_stack[ix] = malloc(COLOUR_NUM * sizeof(COLORREF));
    if (colours_stack[ix])
      colours_num++;
  }
  if (colours_stack[ix])
    memcpy(colours_stack[ix], colours, COLOUR_NUM * sizeof(COLORREF));
}
