gg_color_map_destroy (gGraphColorMapPtr ptr)
{

    gGraphColorMapEntryPtr p;
    gGraphColorMapEntryPtr pn;
    if (!ptr)
	return;
    p = ptr->first;
    while (p)
      {
	  pn = p->next;
	  free (p);
	  p = pn;
      }
    if (ptr->array)
	free (ptr->array);
    free (ptr);
}
