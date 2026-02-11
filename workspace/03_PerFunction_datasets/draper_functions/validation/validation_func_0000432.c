objc_begin_try_stmt (location_t try_locus, tree body)
{
  struct objc_try_context *c = XCNEW (struct objc_try_context);
  c->outer = cur_try_context;
  c->try_body = body;
  c->try_locus = try_locus;
  c->end_try_locus = input_location;
  cur_try_context = c;


  if (flag_objc_sjlj_exceptions)
    objc_mark_locals_volatile (NULL);
}
