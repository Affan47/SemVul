validate_blob (ValidateContext *ctx,
	       guint32          offset,
	       GError         **error)
{
  GITypelib *typelib = ctx->typelib;
  CommonBlob *common;

  if (typelib->len < offset + sizeof (CommonBlob))
    {
      g_set_error (error,
		   G_TYPELIB_ERROR,
		   G_TYPELIB_ERROR_INVALID,
		   "The buffer is too short");
      return FALSE;
    }

  common = (CommonBlob*)&typelib->data[offset];

  switch (common->blob_type)
    {
    case BLOB_TYPE_FUNCTION:
      if (!validate_function_blob (ctx, offset, 0, error))
	return FALSE;
      break;
    case BLOB_TYPE_CALLBACK:
      if (!validate_callback_blob (ctx, offset, error))
	return FALSE;
      break;
    case BLOB_TYPE_STRUCT:
    case BLOB_TYPE_BOXED:
      if (!validate_struct_blob (ctx, offset, common->blob_type, error))
	return FALSE;
      break;
    case BLOB_TYPE_ENUM:
    case BLOB_TYPE_FLAGS:
      if (!validate_enum_blob (ctx, offset, common->blob_type, error))
	return FALSE;
      break;
    case BLOB_TYPE_OBJECT:
      if (!validate_object_blob (ctx, offset, error))
	return FALSE;
      break;
    case BLOB_TYPE_INTERFACE:
      if (!validate_interface_blob (ctx, offset, error))
	return FALSE;
      break;
    case BLOB_TYPE_CONSTANT:
      if (!validate_constant_blob (typelib, offset, error))
	return FALSE;
      break;
    case BLOB_TYPE_UNION:
      if (!validate_union_blob (typelib, offset, error))
	return FALSE;
      break;
    default:
      g_set_error (error,
		   G_TYPELIB_ERROR,
		   G_TYPELIB_ERROR_INVALID_ENTRY,
		   "Invalid blob type");
      return FALSE;
    }

  return TRUE;
}
