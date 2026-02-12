bool InstanceKlass::verify_code(bool throw_verifyerror, TRAPS) {

  Verifier::Mode mode =
    throw_verifyerror ? Verifier::ThrowException : Verifier::NoException;
  return Verifier::verify(this, mode, should_verify_class(), THREAD);
}
