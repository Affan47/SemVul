void TFE_Py_TapeSetRemove(PyObject* tape) {
  auto* stack = GetTapeSet();
  if (stack != nullptr) {
    stack->erase(reinterpret_cast<TFE_Py_Tape*>(tape));
  }


  Py_DECREF(tape);
}
