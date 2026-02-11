fso_gsm_mbpi_database_handleChildren (FsoGsmMBPIDatabase* self, xmlNode* node) {
	g_return_if_fail (self != NULL);
	{
		xmlNode* iter = NULL;
		xmlNode* _tmp0_ = NULL;
		xmlNode* _tmp1_ = NULL;
		_tmp0_ = node;
		_tmp1_ = _tmp0_->children;
		iter = _tmp1_;
		{
			gboolean _tmp2_ = FALSE;
			_tmp2_ = TRUE;
			while (TRUE) {
				gboolean _tmp3_ = FALSE;
				xmlNode* _tmp6_ = NULL;
				xmlNode* _tmp7_ = NULL;
				xmlElementType _tmp8_ = 0;
				xmlNode* _tmp9_ = NULL;
				_tmp3_ = _tmp2_;
				if (!_tmp3_) {
					xmlNode* _tmp4_ = NULL;
					xmlNode* _tmp5_ = NULL;
					_tmp4_ = iter;
					_tmp5_ = _tmp4_->next;
					iter = _tmp5_;
				}
				_tmp2_ = FALSE;
				_tmp6_ = iter;
				if (!(_tmp6_ != NULL)) {
					break;
				}
				_tmp7_ = iter;
				_tmp8_ = _tmp7_->type;
				if (_tmp8_ != XML_ELEMENT_NODE) {
					continue;
				}
				_tmp9_ = iter;
				fso_gsm_mbpi_database_parseNode (self, _tmp9_);
			}
		}
	}
}
