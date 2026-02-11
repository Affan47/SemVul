_edsf_persona_store_update_trust_level (EdsfPersonaStore* self) {
	ESourceRegistry* _tmp0_ = NULL;
	EBookClient* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	EBookClient* _tmp4_ = NULL;
	gboolean _tmp5_ = FALSE;
	gboolean _tmp6_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_source_registry;
	_vala_assert (_tmp0_ != NULL, "this._source_registry != null");
	_tmp1_ = self->priv->_addressbook;
	_vala_assert (_tmp1_ != NULL, "this._addressbook != null");
	_tmp2_ = _edsf_persona_store_backend_name_matches (self, "ldap");
	if (_tmp2_) {
		folks_persona_store_set_trust_level ((FolksPersonaStore*) self, FOLKS_PERSONA_STORE_TRUST_PARTIAL);
		return;
	}
	_tmp3_ = _edsf_persona_store_is_google_contacts_address_book (self);
	if (_tmp3_) {
		folks_persona_store_set_trust_level ((FolksPersonaStore*) self, FOLKS_PERSONA_STORE_TRUST_FULL);
	}
	_tmp4_ = self->priv->_addressbook;
	g_object_get ((EClient*) G_TYPE_CHECK_INSTANCE_CAST (_tmp4_, e_book_client_get_type (), EBookClient), "readonly", &_tmp5_, NULL);
	_tmp6_ = _tmp5_;
	if (_tmp6_) {
		folks_persona_store_set_trust_level ((FolksPersonaStore*) self, FOLKS_PERSONA_STORE_TRUST_PARTIAL);
	} else {
		folks_persona_store_set_trust_level ((FolksPersonaStore*) self, FOLKS_PERSONA_STORE_TRUST_FULL);
	}
}
