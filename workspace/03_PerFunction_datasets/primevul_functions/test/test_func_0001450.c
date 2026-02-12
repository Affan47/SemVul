Graph::Graph(const FunctionLibraryDefinition& flib_def)
    : Graph(flib_def.default_registry()) {

  if (flib_def.num_functions() > 0 && versions_->min_consumer() < 12) {
    versions_->set_min_consumer(12);
  }
  Status s = ops_.AddLibrary(flib_def);
  CHECK(s.ok()) << s.error_message();
}
