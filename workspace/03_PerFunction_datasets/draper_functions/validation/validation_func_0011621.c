WXMPMeta_GetStructField_1 ( XMPMetaRef		 xmpObjRef,
							XMP_StringPtr	 schemaNS,
							XMP_StringPtr	 structName,
							XMP_StringPtr	 fieldNS,
							XMP_StringPtr	 fieldName,
							void *	         fieldValue,
							XMP_OptionBits * options,
							SetClientStringProc SetClientString,
							WXMP_Result *	 wResult )
{
	XMP_ENTER_ObjRead ( XMPMeta, "WXMPMeta_GetStructField_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (structName == 0) || (*structName == 0) ) XMP_Throw ( "Empty struct name", kXMPErr_BadXPath );
		if ( (fieldNS == 0) || (*fieldNS == 0) ) XMP_Throw ( "Empty field namespace URI", kXMPErr_BadSchema );
		if ( (fieldName == 0) || (*fieldName == 0) ) XMP_Throw ( "Empty field name", kXMPErr_BadXPath );

		XMP_StringPtr valuePtr = 0;
		XMP_StringLen valueSize = 0;
		if ( options == 0 ) options = &voidOptionBits;

		bool found = thiz.GetStructField ( schemaNS, structName, fieldNS, fieldName, &valuePtr, &valueSize, options );
		wResult->int32Result = found;

		if ( found && (fieldValue != 0) ) (*SetClientString) ( fieldValue, valuePtr, valueSize );

	XMP_EXIT
}
