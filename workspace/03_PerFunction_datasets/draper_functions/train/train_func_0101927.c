get_scalar_value(const char* as_something) const {
	VObject* unconst_this=const_cast<VObject*>(this);
	if(Value* scalar=fclass.get_scalar(*unconst_this))
		if(Junction* junction=scalar->get_junction())
			if(const Method *method=junction->method){
				VMethodFrame frame(*method, 0 , *unconst_this);

				Value *param;

				if(size_t param_count=frame.method_params_count()){
					if(param_count==1){
						param=new VString(*new String(as_something));
						frame.store_params(&param, 1);
					} else
						throw Exception(PARSER_RUNTIME,
							0,
							"scalar getter method can't have more then 1 parameter (has %d parameters)", param_count);
				}

				pa_thread_request().execute_method(frame);
				return &frame.result().as_value();
			}
	return 0;
}
