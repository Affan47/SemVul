SWIG_Python_ConvertFunctionPtr(PyObject *obj, void **ptr, swig_type_info *ty) {
  if (!PyCFunction_Check(obj)) {
    return SWIG_ConvertPtr(obj, ptr, ty, 0);
  } else {
    void *vptr = 0;


    const char *doc = (((PyCFunctionObject *)obj) -> m_ml -> ml_doc);
    const char *desc = doc ? strstr(doc, "swig_ptr: ") : 0;
    if (desc)
      desc = ty ? SWIG_UnpackVoidPtr(desc + 10, &vptr, ty->name) : 0;
    if (!desc)
      return SWIG_ERROR;
    if (ty) {
      swig_cast_info *tc = SWIG_TypeCheck(desc,ty);
      if (tc) {
        int newmemory = 0;
        *ptr = SWIG_TypeCast(tc,vptr,&newmemory);
        assert(!newmemory);
      } else {
        return SWIG_ERROR;
      }
    } else {
      *ptr = vptr;
    }
    return SWIG_OK;
  }
}
