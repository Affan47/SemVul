int DynamicMetadataMapWrapper::luaSet(lua_State* state) {
  if (iterator_.get() != nullptr) {
    luaL_error(state, "dynamic metadata map cannot be modified while iterating");
  }

  const char* filter_name = luaL_checkstring(state, 2);
  const char* key = luaL_checkstring(state, 3);


  lua_pushvalue(state, 4);

  ProtobufWkt::Struct value;
  (*value.mutable_fields())[key] = Filters::Common::Lua::MetadataMapHelper::loadValue(state);
  streamInfo().setDynamicMetadata(filter_name, value);


  lua_pop(state, 1);
  return 0;
}
