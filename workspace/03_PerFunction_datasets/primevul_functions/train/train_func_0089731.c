PyObject* PyTapeTensor::ZerosLike() const {
  if (GetDType() == tensorflow::DT_RESOURCE) {


    Py_RETURN_NONE;
  }
  if (shape_.index() == 1) {
    PyObject* tensor = absl::get<1>(shape_);
    return py_vspace->ZerosLike(tensor);
  }
  PyObject* py_shape = GetShape();
  PyObject* dtype_field = GetPyDType();
  PyObject* result = py_vspace->Zeros(py_shape, dtype_field);
  Py_DECREF(dtype_field);
  Py_DECREF(py_shape);
  return result;
}
