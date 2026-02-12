static inline TypedValue* makeContainerListHelper(const Variant& a,
                                                  const Array& argv,
                                                  int count,
                                                  int smallestPos) {
  assert(count == argv.size() + 1);
  assert(0 <= smallestPos);
  assert(smallestPos < count);

  TypedValue* containers = req::make_raw_array<TypedValue>(count);
  tvCopy(*a.asCell(), containers[0]);
  int pos = 1;
  for (ArrayIter argvIter(argv); argvIter; ++argvIter, ++pos) {
    const auto& c = *argvIter.secondRef().asCell();
    tvCopy(c, containers[pos]);
  }


  if (smallestPos != 0) {
    TypedValue tmp;
    tvCopy(containers[0], tmp);
    tvCopy(containers[smallestPos], containers[0]);
    tvCopy(tmp, containers[smallestPos]);
  }
  return containers;
}
