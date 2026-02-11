dictview_len(dictviewobject *dv)
{
    Py_ssize_t len = 0;
    if (dv->dv_dict != NULL)
        len = dv->dv_dict->ma_used;
    return len;
}
