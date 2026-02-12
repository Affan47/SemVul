pop_colours(uint ix)
{
  if (ix > 10)
    return;

  if (ix) {
    colours_cur = ix;
    ix--;
  }
  else {
    if (colours_cur) {
      colours_cur--;
      ix = colours_cur;
    }
    else
      return;
  }


  if (colours_stack[ix])
    memcpy(colours, colours_stack[ix], COLOUR_NUM * sizeof(COLORREF));
}
