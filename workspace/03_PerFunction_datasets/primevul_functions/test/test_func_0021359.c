ObjectSetLoadedAttributes(
			  OBJECT          *object,
			  TPM_HANDLE       parentHandle
			  )
{
    OBJECT              *parent = HandleToObject(parentHandle);
    TPMA_OBJECT          objectAttributes = object->publicArea.objectAttributes;


    object->attributes.stClear =
	IS_ATTRIBUTE(objectAttributes, TPMA_OBJECT, stClear);

    if(parent == NULL)
	{
	    object->attributes.primary = SET;
	    switch(parentHandle)
		{
		  case TPM_RH_ENDORSEMENT:
		    object->attributes.epsHierarchy = SET;
		    break;
		  case TPM_RH_OWNER:
		    object->attributes.spsHierarchy = SET;
		    break;
		  case TPM_RH_PLATFORM:
		    object->attributes.ppsHierarchy = SET;
		    break;
		  default:

		    object->attributes.temporary = SET;
		    object->attributes.primary = CLEAR;
		    break;
		}
	}
    else
	{

	    object->attributes.stClear =
		(IS_ATTRIBUTE(objectAttributes, TPMA_OBJECT, stClear)
		 || (parent->attributes.stClear == SET));
	    object->attributes.epsHierarchy = parent->attributes.epsHierarchy;
	    object->attributes.spsHierarchy = parent->attributes.spsHierarchy;
	    object->attributes.ppsHierarchy = parent->attributes.ppsHierarchy;


	    object->attributes.temporary = parent->attributes.temporary
					   || object->attributes.external;
	}


    if(object->attributes.external)
	object->qualifiedName = object->name;
    else
	{

	    if(IS_ATTRIBUTE(objectAttributes, TPMA_OBJECT, restricted)
	       && !object->attributes.publicOnly
	       && IS_ATTRIBUTE(objectAttributes, TPMA_OBJECT, decrypt)
	       && object->publicArea.nameAlg != TPM_ALG_NULL)
		{


		    if(object->publicArea.type == TPM_ALG_KEYEDHASH)
			object->attributes.derivation = SET;
		    else
			object->attributes.isParent = SET;
		}
	    ComputeQualifiedName(parentHandle, object->publicArea.nameAlg,
				 &object->name, &object->qualifiedName);
	}

    ObjectSetInUse(object);
    return;
}
