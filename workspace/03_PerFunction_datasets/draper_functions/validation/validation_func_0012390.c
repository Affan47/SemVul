unity_internal_default_scope_dbus_impl_real_get_metadata (UnityProtocolScopeService* base) {
	GHashTable* result;
	UnityInternalDefaultScopeDBusImpl* self;
	UnitySchema* schema = NULL;
	UnityAbstractScope* _tmp0_ = NULL;
	UnitySchema* _tmp1_ = NULL;
	GHashTable* required_schema = NULL;
	GHashFunc _tmp2_ = NULL;
	GEqualFunc _tmp3_ = NULL;
	GHashTable* _tmp4_ = NULL;
	UnitySchema* _tmp5_ = NULL;
	GList* _tmp6_ = NULL;
	self = (UnityInternalDefaultScopeDBusImpl*) base;
	_tmp0_ = self->priv->_owner;
	_tmp1_ = unity_abstract_scope_get_schema (_tmp0_);
	schema = _tmp1_;
	_tmp2_ = g_str_hash;
	_tmp3_ = g_str_equal;
	_tmp4_ = g_hash_table_new_full (_tmp2_, _tmp3_, _g_free0_, _g_free0_);
	required_schema = _tmp4_;
	_tmp5_ = schema;
	_tmp6_ = unity_schema_get_fields (_tmp5_);
	{
		GList* field_collection = NULL;
		GList* field_it = NULL;
		field_collection = _tmp6_;
		for (field_it = field_collection; field_it != NULL; field_it = field_it->next) {
			UnitySchemaFieldInfo* field = NULL;
			field = (UnitySchemaFieldInfo*) field_it->data;
			{
				UnitySchemaFieldInfo* _tmp7_ = NULL;
				UnitySchemaFieldType _tmp8_ = 0;
				_tmp7_ = field;
				_tmp8_ = (*_tmp7_).type;
				if (_tmp8_ == UNITY_SCHEMA_FIELD_TYPE_REQUIRED) {
					GHashTable* _tmp9_ = NULL;
					UnitySchemaFieldInfo* _tmp10_ = NULL;
					const gchar* _tmp11_ = NULL;
					gchar* _tmp12_ = NULL;
					UnitySchemaFieldInfo* _tmp13_ = NULL;
					const gchar* _tmp14_ = NULL;
					gchar* _tmp15_ = NULL;
					_tmp9_ = required_schema;
					_tmp10_ = field;
					_tmp11_ = (*_tmp10_).name;
					_tmp12_ = g_strdup (_tmp11_);
					_tmp13_ = field;
					_tmp14_ = (*_tmp13_).schema;
					_tmp15_ = g_strdup (_tmp14_);
					g_hash_table_insert (_tmp9_, _tmp12_, _tmp15_);
				}
			}
		}
		_g_list_free0 (field_collection);
	}
	result = required_schema;
	_g_object_unref0 (schema);
	return result;
}
