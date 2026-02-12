pwg_ppdize_resolution(
    ipp_attribute_t *attr,
    int             element,
    int             *xres,
    int             *yres,
    char            *name,
    size_t          namesize)
{
  ipp_res_t units;


  *xres = ippGetResolution(attr, element, yres, &units);

  if (units == IPP_RES_PER_CM)
  {
    *xres = (int)(*xres * 2.54);
    *yres = (int)(*yres * 2.54);
  }

  if (name && namesize > 4)
  {
    if (*xres == *yres)
      snprintf(name, namesize, "%ddpi", *xres);
    else
      snprintf(name, namesize, "%dx%ddpi", *xres, *yres);
  }
}
