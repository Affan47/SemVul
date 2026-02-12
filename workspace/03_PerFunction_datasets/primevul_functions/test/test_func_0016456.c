void InstanceKlass::initialize(TRAPS) {
  if (this->should_be_initialized()) {
    initialize_impl(CHECK);


  } else {
    assert(is_initialized(), "sanity check");
  }
}
