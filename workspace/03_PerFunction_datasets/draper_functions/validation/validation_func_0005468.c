call_method_function( EnvT* e)
  {
    StackGuard<EnvStackT> guard( e->Interpreter()->CallStack());

    int nParam=e->NParam();
    if( nParam < 2)
      e->Throw(  "Name and object reference"
			  " must be specified.");

    DString callP;
    e->AssureScalarPar<DStringGDL>( 0, callP);


    callP = StrUpCase( callP);

    DStructGDL* oStruct = e->GetObjectPar( 1);

    DFun* method= oStruct->Desc()->GetFun( callP);

    if( method == NULL)
      e->Throw( "Method not found: "+callP);

    e->PushNewEnvUD( method, 2, (DObjGDL**) &e->GetPar( 1));


    return e->Interpreter()->call_fun( method->GetTree());
  }
