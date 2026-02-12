PyObject* TFE_Py_RegisterVSpace(PyObject* e) {
  if (py_vspace != nullptr) {
    if (HasAccumulator()) {


      MaybeRaiseExceptionFromStatus(
          tensorflow::errors::Internal(
              "Can't change the vspace implementation while a "
              "forward accumulator is active."),
          nullptr);
    }
    delete py_vspace;
  }

  py_vspace = new PyVSpace(e);
  auto status = py_vspace->Initialize();
  if (MaybeRaiseExceptionFromStatus(status, nullptr)) {
    delete py_vspace;
    return nullptr;
  }

  Py_RETURN_NONE;
}
