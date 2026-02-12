FunctionLibraryDefinition::FunctionDefAndOpRegistration::
    FunctionDefAndOpRegistration(const FunctionDef& fdef_in,
                                 const StackTracesMap& stack_traces)
    : fdef(fdef_in),


      op_registration_data(fdef.signature(), shape_inference::UnknownShape,
                           true ),
      stack_traces(stack_traces) {}
