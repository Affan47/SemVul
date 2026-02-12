bool InstanceKlass::verify_code(TRAPS) {

  return Verifier::verify(this, should_verify_class(), THREAD);
}
