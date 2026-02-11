read_handler(Element *e, void *thunk)
{
    RandomSample *rs = static_cast<RandomSample *>(e);
    switch ((intptr_t)thunk) {
      case 0:
	return cp_unparse_real2(rs->_sampling_prob, SAMPLING_SHIFT);
      case 1:
	return cp_unparse_bool(rs->_active);
      case 2:
	return String(rs->_drops);
      case 3:
	return cp_unparse_real2((1 << SAMPLING_SHIFT) - rs->_sampling_prob, SAMPLING_SHIFT);
      default:
	return "<error>";
    }
}
