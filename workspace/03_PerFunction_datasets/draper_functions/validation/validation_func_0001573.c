_get_path_from_gfid_loc (xlator_t *this, xlator_t *readdir_xl, loc_t *child,
                         char **fpath, gf_boolean_t *missing)
{
        dict_t          *xattr = NULL;
        char            *path = NULL;
        int             ret = -1;

        ret = syncop_getxattr (readdir_xl, child, &xattr, GFID_TO_PATH_KEY);
        if (ret < 0) {
                if ((errno == ENOENT) && missing)
                        *missing = _gf_true;
                goto out;
        }
        ret = dict_get_str (xattr, GFID_TO_PATH_KEY, &path);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "Failed to get path for "
                        "gfid %s", uuid_utoa (child->gfid));
                goto out;
        }
        path = gf_strdup (path);
        if (!path) {
                ret = -1;
                goto out;
        }
        ret = 0;
out:
        if (!ret)
                *fpath = path;
        if (xattr)
                dict_unref (xattr);
        return ret;
}
