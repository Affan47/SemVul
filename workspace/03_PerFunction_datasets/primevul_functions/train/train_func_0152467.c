load_fontset_data(
    XOC		oc,
    FontSet	font_set)
{
    Display	*dpy = oc->core.om->core.display;

    if(font_set->font_name == (char *)NULL) return False ;


    if(font_set->font == NULL) {
       font_set->font = XLoadQueryFont(dpy, font_set->font_name);
       if (font_set->font == NULL){
		return False;
       }
    }
    return True;
}
