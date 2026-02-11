scm_c_with_throw_handler (SCM tag,
			  scm_t_catch_body body,
			  void *body_data,
			  scm_t_catch_handler handler,
			  void *handler_data,
			  int lazy_catch_p)
{
  SCM pre_unwind, answer;
  struct pre_unwind_data c;

  c.handler = handler;
  c.handler_data = handler_data;
  c.running = 0;
  c.lazy_catch_p = lazy_catch_p;
  pre_unwind = make_pre_unwind_data (&c);

  SCM_CRITICAL_SECTION_START;
  scm_i_set_dynwinds (scm_acons (tag, pre_unwind, scm_i_dynwinds ()));
  SCM_CRITICAL_SECTION_END;

  answer = (*body) (body_data);

  SCM_CRITICAL_SECTION_START;
  scm_i_set_dynwinds (SCM_CDR (scm_i_dynwinds ()));
  SCM_CRITICAL_SECTION_END;

  return answer;
}
