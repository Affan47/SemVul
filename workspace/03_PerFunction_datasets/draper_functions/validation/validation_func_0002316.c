I_fopen_subgroup_file_new(const char *group,
				const char *subgroup, const char *file)
{
    FILE *fd;
    char element[GNAME_MAX * 2];


    sprintf(element, "%s/subgroup/%s", group, subgroup);
    G__make_mapset_element_misc("group", element);


    sprintf(element, "subgroup/%s/%s", subgroup, file);

    fd = G_fopen_new_misc("group", element, group);
    if (!fd)
	G_warning(_("Unable to create file [%s] for subgroup [%s] of group [%s in %s]"),
		  file, subgroup, group, G_mapset());

    return fd;
}
