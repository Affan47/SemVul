ce_StructGDLtoIDL( EnvT* e, const BaseGDL* par, SizeT* length, SizeT myAlign)
    {
	SizeT totalSize = ce_LengthOfIDLStruct( e, par, myAlign);
	if (length != NULL) {*length = totalSize;}

	SizeT nEl       = par->N_Elements();
	void* IDLStruct = malloc(nEl * totalSize);
	if (IDLStruct == NULL) {
	    e->Throw("Internal error allocating memory for IDLStruct");
	}

	DStructGDL* s = (DStructGDL*) par;
	SizeT nTags   = s->Desc()->NTags();

	for (SizeT iEl=0; iEl < nEl; iEl++) {
	    char* p = (char*) IDLStruct + iEl*totalSize;
	    for (SizeT iTag=0; iTag < nTags; iTag++) {
		BaseGDL* member = s->GetTag(iTag, iEl);
		DType    pType  = member->Type();
		SizeT length;
		SizeT sizeOf;
		void* source;
		int   doFree = 0;
		if (NumericType(pType) || pType == GDL_PTR || pType == GDL_OBJ) {
		    source = (void*) member->DataAddr();
		    length = member->NBytes();
		    sizeOf = member->Sizeof();
		}
		else if (pType == GDL_STRING) {
		    source = (void*) ce_StringGDLtoIDL(e, member);
		    length = member->N_Elements() * sizeof(EXTERN_STRING);
		    sizeOf = 8;
		    doFree = 1;
		}
		else if (pType == GDL_STRUCT) {
		    source = ce_StructGDLtoIDL( e, member, &length, myAlign );
		    length *= member->N_Elements();
		    sizeOf = 8;
		}
		else {
		    e->Throw("Unsupported type in structure: " + i2s(pType) );
		}
		SizeT align = sizeOf < myAlign ? sizeOf : myAlign;
		if ((SizeT)p % align) {
		    SizeT space = align - (SizeT)p % align;
		    p += space;
		}
		memcpy(p, source, length);
		p+=length;
		if (doFree) {free(source);}

	    }
	}

	return IDLStruct;
    }
