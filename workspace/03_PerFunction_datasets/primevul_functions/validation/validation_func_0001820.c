void* Init(TfLiteContext* context, const char* buffer, size_t length) {


  auto* op_data = new OpData();
  context->AddTensors(context, 6,
                      &op_data->scratch_tensor_index);
  return op_data;
}
