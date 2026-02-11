_wrap_svn_repos_fs_change_rev_prop2(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  svn_repos_t *arg1 = (svn_repos_t *) 0 ;
  svn_revnum_t arg2 ;
  char *arg3 = (char *) 0 ;
  char *arg4 = (char *) 0 ;
  svn_string_t *arg5 = (svn_string_t *) 0 ;
  svn_repos_authz_func_t arg6 = (svn_repos_authz_func_t) 0 ;
  void *arg7 = (void *) 0 ;
  apr_pool_t *arg8 = (apr_pool_t *) 0 ;
  apr_pool_t *_global_pool = NULL ;
  PyObject *_global_py_pool = NULL ;
  svn_string_t value5 ;
  PyObject * obj0 = 0 ;
  PyObject * obj1 = 0 ;
  PyObject * obj4 = 0 ;
  PyObject * obj5 = 0 ;
  PyObject * obj6 = 0 ;
  svn_error_t *result = 0 ;

  if (svn_swig_py_get_pool_arg(args, SWIGTYPE_p_apr_pool_t,
      &_global_py_pool, &_global_pool))
  SWIG_fail;
  arg8 = _global_pool;
  if (!PyArg_ParseTuple(args,(char *)"OOssOO|O:svn_repos_fs_change_rev_prop2",&obj0,&obj1,&arg3,&arg4,&obj4,&obj5,&obj6)) SWIG_fail;
  {
    arg1 = (svn_repos_t *)svn_swig_MustGetPtr(obj0, SWIGTYPE_p_svn_repos_t, svn_argnum_obj0);
    if (PyErr_Occurred()) {
      SWIG_fail;
    }
  }
  {
    arg2 = (svn_revnum_t)SWIG_As_long (obj1);
    if (SWIG_arg_fail(svn_argnum_obj1)) {
      SWIG_fail;
    }
  }
  {
    if (obj4 == Py_None)
    arg5 = NULL;
    else {
      if (!PyString_Check(obj4)) {
        PyErr_SetString(PyExc_TypeError, "not a string");
        SWIG_fail;
      }
      value5.data = PyString_AS_STRING(obj4);
      value5.len = PyString_GET_SIZE(obj4);
      arg5 = &value5;
    }
  }
  {

    arg6 = svn_swig_py_repos_authz_func;
    arg7 = obj5;
  }
  if (obj6) {

    if (obj6 != Py_None && obj6 != _global_py_pool) {
      SWIG_Python_TypeError(SWIG_TypePrettyName(SWIGTYPE_p_apr_pool_t), obj6);
      SWIG_arg_fail(svn_argnum_obj6);
      SWIG_fail;
    }
  }
  {
    svn_swig_py_release_py_lock();

    result = (svn_error_t *)svn_repos_fs_change_rev_prop2(arg1,arg2,(char const *)arg3,(char const *)arg4,(struct svn_string_t const *)arg5,arg6,arg7,arg8);

    svn_swig_py_acquire_py_lock();

  }
  {
    if (result != NULL) {
      if (result->apr_err != SVN_ERR_SWIG_PY_EXCEPTION_SET)
      svn_swig_py_svn_exception(result);
      else
      svn_error_clear(result);
      SWIG_fail;
    }
    Py_INCREF(Py_None);
    resultobj = Py_None;
  }
  {
    Py_XDECREF(_global_py_pool);
  }
  return resultobj;
fail:
  {
    Py_XDECREF(_global_py_pool);
  }
  return NULL;
}
