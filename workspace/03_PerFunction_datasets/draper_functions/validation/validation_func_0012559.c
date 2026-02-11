_wrap_new_apol_mls_range_t(ClientData clientData SWIGUNUSED, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  Tcl_Obj *CONST *argv = objv+1;
  int argc = objc-1;
  if (argc == 0) {
    return _wrap_new_apol_mls_range_t__SWIG_0(clientData, interp, objc, argv - 1);
  }
  if (argc == 1) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_mls_range_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_apol_mls_range_t__SWIG_1(clientData, interp, objc, argv - 1);
    }
  }
  if (argc == 1) {
    int _v;
    int res = SWIG_AsCharPtrAndSize(argv[0], 0, NULL, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      return _wrap_new_apol_mls_range_t__SWIG_3(clientData, interp, objc, argv - 1);
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_policy_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      void *vptr = 0;
      int res = SWIG_ConvertPtr(argv[1], &vptr, SWIGTYPE_p_qpol_mls_range_t, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_apol_mls_range_t__SWIG_4(clientData, interp, objc, argv - 1);
      }
    }
  }
  if (argc == 2) {
    int _v;
    void *vptr = 0;
    int res = SWIG_ConvertPtr(argv[0], &vptr, SWIGTYPE_p_apol_policy_t, 0);
    _v = SWIG_CheckState(res);
    if (_v) {
      int res = SWIG_AsCharPtrAndSize(argv[1], 0, NULL, 0);
      _v = SWIG_CheckState(res);
      if (_v) {
        return _wrap_new_apol_mls_range_t__SWIG_2(clientData, interp, objc, argv - 1);
      }
    }
  }

  Tcl_SetResult(interp,(char *) "Wrong number or type of arguments for overloaded function 'new_apol_mls_range_t'.\n"
    "  Possible C/C++ prototypes are:\n"
    "    apol_mls_range_t::apol_mls_range_t()\n"
    "    apol_mls_range_t::apol_mls_range_t(apol_mls_range_t *)\n"
    "    apol_mls_range_t::apol_mls_range_t(apol_policy_t *,char const *)\n"
    "    apol_mls_range_t::apol_mls_range_t(char const *)\n"
    "    apol_mls_range_t::apol_mls_range_t(apol_policy_t *,qpol_mls_range_t *)\n", TCL_STATIC);
  return TCL_ERROR;
}
