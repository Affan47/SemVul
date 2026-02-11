_IsFortranContiguous(Py_buffer *view)
{
    Py_ssize_t sd, dim;
    int i;

    if (view->ndim == 0) return 1;
    if (view->strides == NULL) return (view->ndim == 1);

    sd = view->itemsize;
    if (view->ndim == 1) return (view->shape[0] == 1 ||
                               sd == view->strides[0]);
    for (i=0; i<view->ndim; i++) {
        dim = view->shape[i];
        if (dim == 0) return 1;
        if (view->strides[i] != sd) return 0;
        sd *= dim;
    }
    return 1;
}
