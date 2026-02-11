scope_varfetch_reference( EnvT* e)
  {
    SizeT nParam=e->NParam();

    EnvStackT& callStack = e->Interpreter()->CallStack();


    DLong curlevnum = callStack.size();


    static int levelIx = e->KeywordIx( "LEVEL" );

    DLongGDL* level = e->IfDefGetKWAs<DLongGDL>( levelIx);

    DLong desiredlevnum = 0;

    if (level != NULL)
      desiredlevnum = (*level)[0];

    if (desiredlevnum <= 0) desiredlevnum += curlevnum;
    if (desiredlevnum < 1) desiredlevnum = 1;
    else if (desiredlevnum > curlevnum) desiredlevnum = curlevnum;

    DSubUD* pro = static_cast<DSubUD*>(callStack[desiredlevnum-1]->GetPro());

    SizeT nVar = pro->Size();
    int nKey = pro->NKey();

    DString varName;

    e->AssureScalarPar<DStringGDL>( 0, varName);
    varName = StrUpCase( varName);
    int xI = pro->FindVar( varName);
    if (xI != -1)
    {

      BaseGDL*& par = callStack[desiredlevnum-1]->GetKW( xI);


      return &par;
    }

    e->Throw( "LVariable not found: " + varName);
    return NULL;
  }
