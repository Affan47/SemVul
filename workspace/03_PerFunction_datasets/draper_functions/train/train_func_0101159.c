fdf_species_index(gchar *atom_label, GSList *species_list)
{
gint i;
struct species_pak *species;
GSList *list;


i=1;
for (list=species_list ; list ; list=g_slist_next(list))
  {
  species = list->data;

  if (g_ascii_strcasecmp(atom_label, species->label) == 0)
    return(i);

  i++;
  }
return(0);
}
