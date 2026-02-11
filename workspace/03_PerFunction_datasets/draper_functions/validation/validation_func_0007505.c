GetIndexedPropertiesExternalArrayDataType() {
  ON_BAILOUT("v8::GetIndexedPropertiesExternalArrayDataType()",
             return static_cast<ExternalArrayType>(-1));
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  switch (self->elements()->map()->instance_type()) {
    case i::EXTERNAL_BYTE_ARRAY_TYPE:
      return kExternalByteArray;
    case i::EXTERNAL_UNSIGNED_BYTE_ARRAY_TYPE:
      return kExternalUnsignedByteArray;
    case i::EXTERNAL_SHORT_ARRAY_TYPE:
      return kExternalShortArray;
    case i::EXTERNAL_UNSIGNED_SHORT_ARRAY_TYPE:
      return kExternalUnsignedShortArray;
    case i::EXTERNAL_INT_ARRAY_TYPE:
      return kExternalIntArray;
    case i::EXTERNAL_UNSIGNED_INT_ARRAY_TYPE:
      return kExternalUnsignedIntArray;
    case i::EXTERNAL_FLOAT_ARRAY_TYPE:
      return kExternalFloatArray;
    default:
      return static_cast<ExternalArrayType>(-1);
  }
}
