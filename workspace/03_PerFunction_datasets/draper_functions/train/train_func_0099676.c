HeapFreeObj( EnvT* env, BaseGDL* var, bool verbose)
  {
    if( var == NULL)
      return;
    if( var->Type() == GDL_STRUCT)
    {
      DStructGDL* varStruct = static_cast<DStructGDL*>( var);
      DStructDesc* desc = varStruct->Desc();
      for( SizeT e=0; e<varStruct->N_Elements(); ++e)
	for( SizeT t=0; t<desc->NTags(); ++t)
	{
	    BaseGDL* actElementTag = varStruct->GetTag( t, e);
	    HeapFreeObj( env, actElementTag, verbose);
	}
    }
    else if( var->Type() == GDL_PTR)
    {

      DPtrGDL* varPtr = static_cast<DPtrGDL*>( var);
      for( SizeT e=0; e<varPtr->N_Elements(); ++e)
      {
	DPtr actPtrID = (*varPtr)[e];
	if( actPtrID == 0)
	  continue;

	BaseGDL* derefPtr = DInterpreter::GetHeap( actPtrID);
	HeapFreeObj( env, derefPtr, verbose);
      }
    }
    else if( var->Type() == GDL_OBJ)
    {
      DObjGDL* varObj = static_cast<DObjGDL*>( var);
      for( SizeT e=0; e<varObj->N_Elements(); ++e)
      {
	DObj actID = (*varObj)[e];
	if( actID == 0)
	  continue;

	if( verbose)
	{
	  BaseGDL* derefObj = DInterpreter::GetObjHeap( actID);
	  help_item( cout,
		      derefObj, DString( "<ObjHeapVar")+
		      i2s(actID)+">",
		      false);
	}

	env->ObjCleanup( actID);
      }
    }
  }
