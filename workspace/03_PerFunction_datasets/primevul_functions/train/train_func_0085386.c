TypedValue HHVM_FUNCTION(array_intersect,
                         const Variant& container1,
                         const Variant& container2,
                         const Array& args ) {
  ARRAY_INTERSECT_PRELUDE()


  auto st = req::make<c_Set>();
  if (LIKELY(!moreThanTwo)) {


    containerValuesToSetHelper(st, container2);
  } else {


    int count = args.size() + 1;
    TypedValue* containers =
      makeContainerListHelper(container2, args, count, smallestPos);
    SCOPE_EXIT { req::free(containers); };

    containerValuesIntersectHelper(st, containers, count);
  }


  Variant strHolder(empty_string_variant());
  TypedValue* strTv = strHolder.asTypedValue();
  bool isKey = isArrayType(c1.m_type);
  for (ArrayIter iter(container1); iter; ++iter) {
    const auto& val = iter.secondRefPlus();
    const auto& c = *val.asCell();
    if (!checkSetHelper(st, c, strTv, true)) continue;
    ret.setWithRef(iter.first(), val, isKey);
  }
  return tvReturn(std::move(ret));
}
