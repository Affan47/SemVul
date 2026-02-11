GVL_load_vol(int id, const char *filename)
{
    geovol *gvl;
    int handle;

    G_debug(3, "GVL_load_vol(): id=%d, name=%s",
	    id, filename);

    if (NULL == (gvl = gvl_get_vol(id))) {
	return (-1);
    }

    G_message(_("Loading 3d raster map <%s>..."), filename);

    if (0 > (handle = gvl_file_newh(filename, VOL_FTYPE_G3D)))
	return (-1);

    gvl->hfile = handle;

    return (0);
}
