qtreetbl_put_by_obj(qtreetbl_t *tbl, const void *name, size_t namesize,
                         const void *data, size_t datasize) {
    if (name == NULL || namesize == 0 || data == NULL || datasize == 0) {
        errno = EINVAL;
        return false;
    }

    qtreetbl_lock(tbl);
    errno = 0;
    qtreetbl_obj_t *root = put_obj(tbl, tbl->root, name, namesize, data,
                                   datasize);
    if (root == NULL || errno == ENOMEM) {
        qtreetbl_unlock(tbl);
        return false;
    }
    root->red = false;
    tbl->root = root;
    qtreetbl_unlock(tbl);

    return true;
}
