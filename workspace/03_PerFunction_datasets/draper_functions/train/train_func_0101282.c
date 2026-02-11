caribou_ikeyboard_object_real_get_keys (CaribouIKeyboardObject* self, int* result_length1) {
	CaribouKeyModel** result = NULL;
	GeeArrayList* keys = NULL;
	GeeArrayList* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	CaribouIKeyboardObject** _tmp2_ = NULL;
	GeeArrayList* _tmp11_ = NULL;
	gint _tmp12_ = 0;
	gpointer* _tmp13_ = NULL;
	CaribouKeyModel** _tmp14_ = NULL;
	gint _tmp14__length1 = 0;
	_tmp0_ = gee_array_list_new (CARIBOU_TYPE_KEY_MODEL, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL, NULL, NULL);
	keys = _tmp0_;
	_tmp2_ = caribou_ikeyboard_object_get_children (self, &_tmp1_);
	{
		CaribouIKeyboardObject** obj_collection = NULL;
		gint obj_collection_length1 = 0;
		gint _obj_collection_size_ = 0;
		gint obj_it = 0;
		obj_collection = _tmp2_;
		obj_collection_length1 = _tmp1_;
		for (obj_it = 0; obj_it < _tmp1_; obj_it = obj_it + 1) {
			CaribouIKeyboardObject* _tmp3_ = NULL;
			CaribouIKeyboardObject* obj = NULL;
			_tmp3_ = _g_object_ref0 (obj_collection[obj_it]);
			obj = _tmp3_;
			{
				CaribouKeyModel** obj_keys = NULL;
				CaribouIKeyboardObject* _tmp4_ = NULL;
				gint _tmp5_ = 0;
				CaribouKeyModel** _tmp6_ = NULL;
				gint obj_keys_length1 = 0;
				gint _obj_keys_size_ = 0;
				CaribouKeyModel** _tmp7_ = NULL;
				gint _tmp7__length1 = 0;
				_tmp4_ = obj;
				_tmp6_ = caribou_ikeyboard_object_get_keys (_tmp4_, &_tmp5_);
				obj_keys = _tmp6_;
				obj_keys_length1 = _tmp5_;
				_obj_keys_size_ = obj_keys_length1;
				_tmp7_ = obj_keys;
				_tmp7__length1 = obj_keys_length1;
				{
					CaribouKeyModel** key_collection = NULL;
					gint key_collection_length1 = 0;
					gint _key_collection_size_ = 0;
					gint key_it = 0;
					key_collection = _tmp7_;
					key_collection_length1 = _tmp7__length1;
					for (key_it = 0; key_it < _tmp7__length1; key_it = key_it + 1) {
						CaribouKeyModel* _tmp8_ = NULL;
						CaribouKeyModel* key = NULL;
						_tmp8_ = _g_object_ref0 (key_collection[key_it]);
						key = _tmp8_;
						{
							GeeArrayList* _tmp9_ = NULL;
							CaribouKeyModel* _tmp10_ = NULL;
							_tmp9_ = keys;
							_tmp10_ = key;
							gee_abstract_collection_add ((GeeAbstractCollection*) _tmp9_, _tmp10_);
							_g_object_unref0 (key);
						}
					}
				}
				obj_keys = (_vala_array_free (obj_keys, obj_keys_length1, (GDestroyNotify) g_object_unref), NULL);
				_g_object_unref0 (obj);
			}
		}
		obj_collection = (_vala_array_free (obj_collection, obj_collection_length1, (GDestroyNotify) g_object_unref), NULL);
	}
	_tmp11_ = keys;
	_tmp13_ = gee_collection_to_array ((GeeCollection*) _tmp11_, &_tmp12_);
	_tmp14_ = (CaribouKeyModel**) _tmp13_;
	_tmp14__length1 = (_tmp12_ * sizeof (CaribouKeyModel*)) / sizeof (CaribouKeyModel*);
	if (result_length1) {
		*result_length1 = _tmp14__length1;
	}
	result = _tmp14_;
	_g_object_unref0 (keys);
	return result;
}
