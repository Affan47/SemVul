_wrap_GooCanvas__do_create_item(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { "self", "model", NULL };
    PyGObject *self, *model;
    GooCanvasItem *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!:GooCanvas.create_item", kwlist, &PyGooCanvas_Type, &self, &PyGooCanvasItemModel_Type, &model))
        return NULL;
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (GOO_CANVAS_CLASS(klass)->create_item)
        ret = GOO_CANVAS_CLASS(klass)->create_item(GOO_CANVAS(self->obj), GOO_CANVAS_ITEM_MODEL(model->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method GooCanvas.create_item not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);

    return pygobject_new((GObject *)ret);
}
