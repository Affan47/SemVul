G__open_misc(const char *dir,
			const char *element,
			const char *name, const char *mapset, int mode)
{
    char path[GPATH_MAX];
    char xname[GNAME_MAX], xmapset[GMAPSET_MAX];


    G__check_gisinit();


    if (mode == 0) {
	if (G__name_is_fully_qualified(name, xname, xmapset)) {
	    if (*mapset && strcmp(xmapset, mapset) != 0) {
 		G_warning(_("G__open_misc(read): mapset <%s> doesn't match xmapset <%s>"),
 			  mapset, xmapset);
		return -1;
	    }
	    name = xname;
	    mapset = xmapset;
	}
	else if (!*mapset)
    	    mapset = G_find_file2_misc(dir, element, name, mapset);

	if (!mapset)
	    return -1;

	G__file_name_misc(path, dir, element, name, mapset);

	return open(path, 0);
    }

    if (mode == 1 || mode == 2) {
	mapset = G_mapset();
	if (G__name_is_fully_qualified(name, xname, xmapset)) {
	    if (strcmp(xmapset, mapset) != 0) {
 		G_warning(_("G__open_misc(write): xmapset <%s> != G_mapset() <%s>"),
			  xmapset, mapset);
		return -1;
	    }
	    name = xname;
	}

	if (G_legal_filename(name) == -1)
	    return -1;

	G__file_name_misc(path, dir, element, name, mapset);
	if (mode == 1 || access(path, 0) != 0) {
	    G__make_mapset_element_misc(dir, name);
	    close(creat(path, 0666));
	}

	return open(path, mode);
    }
    return -1;
}
