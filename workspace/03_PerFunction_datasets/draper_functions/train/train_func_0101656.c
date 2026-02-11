gee_hazard_pointer_context_free (GeeHazardPointerContext* self) {
	gint size = 0;
	GeeArrayList* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gboolean clean_parent = FALSE;
	gint _tmp3_ = 0;
	GeeHazardPointerContext* _tmp18_ = NULL;
	gboolean _tmp19_ = FALSE;
	_tmp0_ = self->_to_free;
	_tmp1_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp0_);
	_tmp2_ = _tmp1_;
	size = _tmp2_;
	clean_parent = FALSE;
	_tmp3_ = size;
	if (_tmp3_ > 0) {
		GeeArrayList* remaining = NULL;
		gboolean _tmp4_ = FALSE;
		GeeHazardPointerContext* _tmp5_ = NULL;
		gboolean _tmp8_ = FALSE;
		GeeArrayList* _tmp13_ = NULL;
		_tmp5_ = self->_parent;
		if (_tmp5_ == NULL) {
			_tmp4_ = TRUE;
		} else {
			gint _tmp6_ = 0;
			guint _tmp7_ = 0U;
			_tmp6_ = size;
			_tmp7_ = gee_hazard_pointer_context_THRESHOLD;
			_tmp4_ = ((guint) _tmp6_) >= _tmp7_;
		}
		_tmp8_ = _tmp4_;
		if (_tmp8_) {
			GeeHazardPointerPolicy* _tmp9_ = NULL;
			GeeArrayList* _tmp10_ = NULL;
			GeeArrayList* _tmp11_ = NULL;
			_tmp9_ = self->_policy;
			_tmp10_ = self->_to_free;
			self->_to_free = NULL;
			_tmp11_ = gee_hazard_pointer_policy_perform (*_tmp9_, _tmp10_);
			_g_object_unref0 (remaining);
			remaining = _tmp11_;
		} else {
			GeeArrayList* _tmp12_ = NULL;
			_tmp12_ = self->_to_free;
			self->_to_free = NULL;
			_g_object_unref0 (remaining);
			remaining = _tmp12_;
		}
		_tmp13_ = remaining;
		if (_tmp13_ != NULL) {
			GeeHazardPointerContext* _tmp14_ = NULL;
			GeeHazardPointerContext* _tmp15_ = NULL;
			GeeArrayList* _tmp16_ = NULL;
			GeeArrayList* _tmp17_ = NULL;
			_tmp14_ = self->_parent;
			_vala_assert (_tmp14_ != NULL, "_parent != null");
			_tmp15_ = self->_parent;
			_tmp16_ = _tmp15_->_to_free;
			_tmp17_ = remaining;
			gee_array_list_add_all (_tmp16_, (GeeCollection*) _tmp17_);
			clean_parent = TRUE;
		}
		_g_object_unref0 (remaining);
	}
	_tmp18_ = self->_parent;
	g_static_private_set (&gee_hazard_pointer_context__current_context, _tmp18_, NULL);
	_tmp19_ = clean_parent;
	if (_tmp19_) {
		GeeHazardPointerContext* _tmp20_ = NULL;
		GeeArrayList* _tmp21_ = NULL;
		_tmp20_ = self->_parent;
		_tmp21_ = _tmp20_->_to_free;
		gee_hazard_pointer_try_free (_tmp21_);
	}
	_g_object_unref0 (self->_to_free);
	_g_free0 (self->_policy);
	g_slice_free (GeeHazardPointerContext, self);
}
