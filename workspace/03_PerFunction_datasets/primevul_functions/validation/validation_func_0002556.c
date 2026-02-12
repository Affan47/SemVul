int asylo_enclave_call(uint64_t selector, void *buffer) {
  SgxParams *const sgx_params = reinterpret_cast<SgxParams *>(buffer);
  if (!IsValidUntrustedAddress(sgx_params)) {
    PrimitiveStatus status{primitives::AbslStatusCode::kInvalidArgument,
                           "input should lie within untrusted memory."};
    return status.error_code();
  }

  const void *input = sgx_params->input;
  size_t input_size = sgx_params->input_size;
  size_t output_size = 0;

  MessageReader in;
  MessageWriter out;


  auto trusted_input = CopyFromUntrusted(input, input_size);
  if (trusted_input) {
    in.Deserialize(trusted_input.get(), input_size);
  }

  PrimitiveStatus status = InvokeEntryHandler(selector, &in, &out);


  output_size = out.MessageSize();
  if (out.MessageSize() > 0) {

    std::unique_ptr<char[]> trusted_output(new char[output_size]);
    out.Serialize(trusted_output.get());
    sgx_params->output = CopyToUntrusted(trusted_output.get(), output_size);
  }
  sgx_params->output_size = static_cast<uint64_t>(output_size);
  return status.error_code();
}
