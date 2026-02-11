evaluate_number(const xpath_node& n) const
	{
		if (!_impl) return impl::gen_nan();

		impl::xpath_context c(n, 1, 1);
		impl::xpath_stack_data sd;

	#ifdef PUGIXML_NO_EXCEPTIONS
		if (setjmp(sd.error_handler)) return impl::gen_nan();
	#endif

		return static_cast<impl::xpath_query_impl*>(_impl)->root->eval_number(c, sd.stack);
	}
