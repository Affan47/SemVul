_wrap_goo_canvas_item_get_requested_height(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "cr", "width", NULL };
    double width, ret;
    PycairoContext *cr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!d:GooCanvasItem.get_requested_height", kwlist, &PycairoContext_Type, &cr, &width))
        return NULL;

    ret = goo_canvas_item_get_requested_height(GOO_CANVAS_ITEM(self->obj), cr->ctx, width);

    return PyFloat_FromDouble(ret);
}
