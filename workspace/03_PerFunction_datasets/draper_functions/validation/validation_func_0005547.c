__pyx_array_MemoryView_5array_10__setitem__(struct __pyx_array_obj *__pyx_v_self, PyObject *__pyx_v_item, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__setitem__", 0);


  __pyx_t_1 = PyObject_GetAttr(((PyObject *)__pyx_v_self), __pyx_n_s__memview); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyObject_SetItem(__pyx_t_1, __pyx_v_item, __pyx_v_value) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("View.MemoryView.array.__setitem__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
