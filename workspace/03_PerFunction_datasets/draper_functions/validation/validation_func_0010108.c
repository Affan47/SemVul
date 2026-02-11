bdf_update_name_from_properties(bdf_font_t *font)
#else
bdf_update_name_from_properties(font)
bdf_font_t *font;
#endif
{
    unsigned long i;
    bdf_property_t *p;
    _bdf_list_t list;
    char *np, name[128], nname[128];

    if (font == 0 || bdf_has_xlfd_name(font) == 0)
      return;

    (void) memset((char *) &list, 0, sizeof(_bdf_list_t));


    i = (unsigned long) strlen(font->name);
    (void) memcpy(name, font->name, i + 1);
    _bdf_split("-", name, i, &list);
    _bdf_shift(1, &list);


    np = nname;
    *np++ = '-';
    *np = 0;

    for (i = 0; i < 14; i++) {
        if ((p = bdf_get_font_property(font, xlfdfields[i])) != 0) {


            switch (p->format) {
              case BDF_ATOM:
                if (p->value.atom != 0)
                  sprintf(np, "%s", p->value.atom);
                break;
              case BDF_CARDINAL:
                sprintf(np, "%ld", p->value.card32);
                break;
              case BDF_INTEGER:
                sprintf(np, "%ld", p->value.int32);
                break;
            }
        } else


          sprintf(np, "%s", list.field[i]);
        np += strlen(np);
        if (i + 1 < 14) {
            *np++ = '-';
            *np = 0;
        }
    }


    free(font->name);
    i = (unsigned long) (strlen(nname) + 1);
    font->name = (char *) malloc(i);
    (void) memcpy(font->name, nname, i);


    if (list.size > 0)
      free((char *) list.field);

    font->modified = 1;
}
