m_explore_and_check (pIIR_ScalarSubtype sst, RegionStack &rstack, bool collect_access_info)
{
  if (done(sst) & EXPLORED) return 0; else  done(sst) |= EXPLORED;

  int error_count = 0;


  if (sst->immediate_base != NULL)
    error_count += explore_and_check (sst->immediate_base, rstack, collect_access_info);
  if (sst->resolution_function != NULL)
    error_count += explore_and_check (sst->resolution_function, rstack, collect_access_info);

  error_count += constant_fold(sst, rstack);

  pIIR_Type basic_type = get_basic_type(sst->immediate_base);
  vector<RangeDescriptor> range_desc = get_discrete_range(sst, rstack, IR_NOT_STATIC);


  static_declarative_region(sst) = RootDeclarativeRegion(rstack);


  if (sst->range == NULL) {

  } else if (sst->base->is(IR_ENUMERATION_TYPE) ||
	     sst->base->is(IR_INTEGER_TYPE) ||
	     sst->base->is(IR_PHYSICAL_TYPE)) {


    StaticRangeDescriptor<lint, IR_Direction> range = range_desc[0].rangedes_to_lint(rstack);

    if (range.valid[0])
      error_count += check_scalar_against_bounds(sst, range.left, basic_type, rstack, runtime_checks(sst), true);
    else
      runtime_checks(sst) |= RT_CHECK_LEFT_BOUND;

    if (range.valid[2])
      error_count += check_scalar_against_bounds(sst, range.right, basic_type, rstack, runtime_checks(sst), true);
    else
      runtime_checks(sst) |= RT_CHECK_RIGHT_BOUND;


    if (!and_reduce(range.valid))
      static_declarative_region(sst) = BaseDeclarativeRegion(rstack);

  } else if (sst->base->is(IR_FLOATING_TYPE)) {


    StaticRangeDescriptor<double, IR_Direction> range = range_desc[0].rangedes_to_double(rstack);

    if (range.valid[0])
      error_count += check_scalar_against_bounds(sst, range.left, basic_type, rstack, runtime_checks(sst), true);
    else
      runtime_checks(sst) |= RT_CHECK_LEFT_BOUND;

    if (range.valid[2])
      error_count += check_scalar_against_bounds(sst, range.right, basic_type, rstack, runtime_checks(sst), true);
    else
      runtime_checks(sst) |= RT_CHECK_RIGHT_BOUND;


    if (!and_reduce(range.valid))
      static_declarative_region(sst) = BaseDeclarativeRegion(rstack);

  } else {
    codegen_error.error("%:error: sorry, this subtype declaration is currently not supported", sst);
    error_count++;
  }

  return error_count;
}
