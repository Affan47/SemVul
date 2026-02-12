bool KernelCacheEnabled(const OpDef& op_def) {
  if (data::DatasetOpKernel::IsDatasetOp(op_def)) {
    return false;
  }


  return true;
}
