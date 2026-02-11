unity_search_metadata_get_location (UnitySearchMetadata* self) {
	UnityGeoCoordinate* result;
	UnityGeoCoordinate* _tmp0_ = NULL;
	static const char EXPECTED_TYPE[] = "(iddd)";
	GHashTable* _tmp2_ = NULL;
	GVariant* location_v = NULL;
	GHashTable* _tmp3_ = NULL;
	gconstpointer _tmp4_ = NULL;
	GVariant* _tmp5_ = NULL;
	gboolean _tmp6_ = FALSE;
	GVariant* _tmp7_ = NULL;
	gboolean _tmp10_ = FALSE;
	gdouble lat = 0.0;
	gdouble lon = 0.0;
	gdouble alt = 0.0;
	gint loc_type = 0;
	GVariant* _tmp11_ = NULL;
	gint _tmp12_ = 0;
	UnityGeoCoordinate* _tmp20_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->geo_coordinate;
	if (_tmp0_ != NULL) {
		UnityGeoCoordinate* _tmp1_ = NULL;
		_tmp1_ = self->priv->geo_coordinate;
		result = _tmp1_;
		return result;
	}
	_tmp2_ = self->priv->all_metadata;
	if (_tmp2_ == NULL) {
		result = NULL;
		return result;
	}
	_tmp3_ = self->priv->all_metadata;
	_tmp4_ = g_hash_table_lookup (_tmp3_, "location");
	_tmp5_ = _g_variant_ref0 ((GVariant*) _tmp4_);
	location_v = _tmp5_;
	_tmp7_ = location_v;
	if (_tmp7_ == NULL) {
		_tmp6_ = TRUE;
	} else {
		GVariant* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		_tmp8_ = location_v;
		_tmp9_ = g_variant_get_type_string (_tmp8_);
		_tmp6_ = g_strcmp0 (_tmp9_, EXPECTED_TYPE) != 0;
	}
	_tmp10_ = _tmp6_;
	if (_tmp10_) {
		result = NULL;
		_g_variant_unref0 (location_v);
		return result;
	}
	_tmp11_ = location_v;
	g_variant_get (_tmp11_, EXPECTED_TYPE, &loc_type, &lat, &lon, &alt, NULL);
	_tmp12_ = loc_type;
	if (_tmp12_ == ((gint) UNITY_GEO_COORDINATE_COORDINATE_TYPE_COORDINATE_3D)) {
		gdouble _tmp13_ = 0.0;
		gdouble _tmp14_ = 0.0;
		gdouble _tmp15_ = 0.0;
		UnityGeoCoordinate* _tmp16_ = NULL;
		_tmp13_ = lat;
		_tmp14_ = lon;
		_tmp15_ = alt;
		_tmp16_ = unity_geo_coordinate_new_with_altitude (_tmp13_, _tmp14_, _tmp15_);
		_g_object_unref0 (self->priv->geo_coordinate);
		self->priv->geo_coordinate = _tmp16_;
	} else {
		gdouble _tmp17_ = 0.0;
		gdouble _tmp18_ = 0.0;
		UnityGeoCoordinate* _tmp19_ = NULL;
		_tmp17_ = lat;
		_tmp18_ = lon;
		_tmp19_ = unity_geo_coordinate_new (_tmp17_, _tmp18_);
		_g_object_unref0 (self->priv->geo_coordinate);
		self->priv->geo_coordinate = _tmp19_;
	}
	_tmp20_ = self->priv->geo_coordinate;
	result = _tmp20_;
	_g_variant_unref0 (location_v);
	return result;
}
