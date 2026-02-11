py_gc_bar_set_repeat_icon(PyObject* self, PyObject* args)
{
  PyObject* pyObject;
  RsvgHandle *svg_handle;


  if(!PyArg_ParseTuple(args, "O:gc_bar_set_repeat_icon", &pyObject))
    return NULL;
  svg_handle = (RsvgHandle*) pygobject_get(pyObject);


  gc_bar_set_repeat_icon(svg_handle);


  Py_INCREF(Py_None);
  return Py_None;
}
