Init_fiddle_function(void)
{


    cFiddleFunction = rb_define_class_under(mFiddle, "Function", rb_cObject);


    rb_define_const(cFiddleFunction, "DEFAULT", INT2NUM(FFI_DEFAULT_ABI));

#ifdef HAVE_CONST_FFI_STDCALL


    rb_define_const(cFiddleFunction, "STDCALL", INT2NUM(FFI_STDCALL));
#endif

    rb_define_alloc_func(cFiddleFunction, allocate);


    rb_define_method(cFiddleFunction, "call", function_call, -1);


    rb_define_method(cFiddleFunction, "initialize", initialize, -1);
}
