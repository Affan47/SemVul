ast_dealloc(AST_object *self)
{

    PyObject_GC_UnTrack(self);
    Py_CLEAR(self->dict);
    Py_TYPE(self)->tp_free(self);
}
