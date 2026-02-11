__pyx_pf_6Cython_8Compiler_7Visitor_10NodeFinder_2visit_Node(struct __pyx_obj_6Cython_8Compiler_7Visitor_NodeFinder *__pyx_v_self, PyObject *__pyx_v_node) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("visit_Node", 0);


  __pyx_t_1 = (__pyx_v_self->found != 0);
  if (__pyx_t_1) {
    goto __pyx_L3;
  }


  __pyx_t_1 = (__pyx_v_node == __pyx_v_self->node);
  __pyx_t_2 = (__pyx_t_1 != 0);
  if (__pyx_t_2) {


    __pyx_v_self->found = 1;
    goto __pyx_L3;
  }
   {


    __pyx_t_3 = ((struct __pyx_vtabstruct_6Cython_8Compiler_7Visitor_NodeFinder *)__pyx_v_self->__pyx_base.__pyx_vtab)->__pyx_base._visitchildren(((struct __pyx_obj_6Cython_8Compiler_7Visitor_TreeVisitor *)__pyx_v_self), __pyx_v_node, Py_None); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 682; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  }
  __pyx_L3:;


  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("Cython.Compiler.Visitor.NodeFinder.visit_Node", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
