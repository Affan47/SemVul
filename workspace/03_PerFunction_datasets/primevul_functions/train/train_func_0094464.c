static int acl_check_password_rights(
	TALLOC_CTX *mem_ctx,
	struct ldb_module *module,
	struct ldb_request *req,
	struct security_descriptor *sd,
	struct dom_sid *sid,
	const struct dsdb_class *objectclass,
	bool userPassword,
	struct  dsdb_control_password_acl_validation **control_for_response)
{
	int ret = LDB_SUCCESS;
	unsigned int del_attr_cnt = 0, add_attr_cnt = 0, rep_attr_cnt = 0;
	unsigned int del_val_cnt = 0, add_val_cnt = 0, rep_val_cnt = 0;
	struct ldb_message_element *el;
	struct ldb_message *msg;
	struct ldb_control *c = NULL;
	const char *passwordAttrs[] = { "userPassword", "clearTextPassword",
					"unicodePwd", NULL }, **l;
	TALLOC_CTX *tmp_ctx = talloc_new(mem_ctx);
	struct dsdb_control_password_acl_validation *pav = NULL;

	if (tmp_ctx == NULL) {
		return LDB_ERR_OPERATIONS_ERROR;
	}

	pav = talloc_zero(req, struct dsdb_control_password_acl_validation);
	if (pav == NULL) {
		talloc_free(tmp_ctx);
		return LDB_ERR_OPERATIONS_ERROR;
	}


	*control_for_response = pav;

	c = ldb_request_get_control(req, DSDB_CONTROL_PASSWORD_CHANGE_OLD_PW_CHECKED_OID);
	if (c != NULL) {
		pav->pwd_reset = false;


		ret = acl_check_extended_right(tmp_ctx,
					       module,
					       req,
					       objectclass,
					       sd,
					       acl_user_token(module),
					       GUID_DRS_USER_CHANGE_PASSWORD,
					       SEC_ADS_CONTROL_ACCESS,
					       sid);
		goto checked;
	}

	c = ldb_request_get_control(req, DSDB_CONTROL_PASSWORD_HASH_VALUES_OID);
	if (c != NULL) {
		pav->pwd_reset = true;


		ret = acl_check_extended_right(tmp_ctx,
					       module,
					       req,
					       objectclass,
					       sd,
					       acl_user_token(module),
					       GUID_DRS_FORCE_CHANGE_PASSWORD,
					       SEC_ADS_CONTROL_ACCESS,
					       sid);
		goto checked;
	}

	el = ldb_msg_find_element(req->op.mod.message, "dBCSPwd");
	if (el != NULL) {


		talloc_free(tmp_ctx);
		return LDB_ERR_UNWILLING_TO_PERFORM;
	}

	msg = ldb_msg_copy_shallow(tmp_ctx, req->op.mod.message);
	if (msg == NULL) {
		return ldb_module_oom(module);
	}
	for (l = passwordAttrs; *l != NULL; l++) {
		if ((!userPassword) && (ldb_attr_cmp(*l, "userPassword") == 0)) {
			continue;
		}

		while ((el = ldb_msg_find_element(msg, *l)) != NULL) {
			if (LDB_FLAG_MOD_TYPE(el->flags) == LDB_FLAG_MOD_DELETE) {
				++del_attr_cnt;
				del_val_cnt += el->num_values;
			}
			if (LDB_FLAG_MOD_TYPE(el->flags) == LDB_FLAG_MOD_ADD) {
				++add_attr_cnt;
				add_val_cnt += el->num_values;
			}
			if (LDB_FLAG_MOD_TYPE(el->flags) == LDB_FLAG_MOD_REPLACE) {
				++rep_attr_cnt;
				rep_val_cnt += el->num_values;
			}
			ldb_msg_remove_element(msg, el);
		}
	}


	if ((del_attr_cnt > 0) && (add_attr_cnt == 0) && (rep_attr_cnt == 0)) {
		talloc_free(tmp_ctx);
		return LDB_SUCCESS;
	}


	if (rep_attr_cnt > 0) {
		pav->pwd_reset = true;

		ret = acl_check_extended_right(tmp_ctx,
					       module,
					       req,
					       objectclass,
					       sd,
					       acl_user_token(module),
					       GUID_DRS_FORCE_CHANGE_PASSWORD,
					       SEC_ADS_CONTROL_ACCESS,
					       sid);
		goto checked;
	}

	if (add_attr_cnt != del_attr_cnt) {
		pav->pwd_reset = true;

		ret = acl_check_extended_right(tmp_ctx,
					       module,
					       req,
					       objectclass,
					       sd,
					       acl_user_token(module),
					       GUID_DRS_FORCE_CHANGE_PASSWORD,
					       SEC_ADS_CONTROL_ACCESS,
					       sid);
		goto checked;
	}

	if (add_val_cnt == 1 && del_val_cnt == 1) {
		pav->pwd_reset = false;

		ret = acl_check_extended_right(tmp_ctx,
					       module,
					       req,
					       objectclass,
					       sd,
					       acl_user_token(module),
					       GUID_DRS_USER_CHANGE_PASSWORD,
					       SEC_ADS_CONTROL_ACCESS,
					       sid);

		if (ret == LDB_ERR_INSUFFICIENT_ACCESS_RIGHTS) {
			ret = LDB_ERR_CONSTRAINT_VIOLATION;
		}
		goto checked;
	}

	if (add_val_cnt == 1 && del_val_cnt == 0) {
		pav->pwd_reset = true;

		ret = acl_check_extended_right(tmp_ctx,
					       module,
					       req,
					       objectclass,
					       sd,
					       acl_user_token(module),
					       GUID_DRS_FORCE_CHANGE_PASSWORD,
					       SEC_ADS_CONTROL_ACCESS,
					       sid);

		if (ret == LDB_ERR_INSUFFICIENT_ACCESS_RIGHTS) {
			ret = LDB_ERR_CONSTRAINT_VIOLATION;
		}
		goto checked;
	}


	talloc_free(tmp_ctx);
	return LDB_SUCCESS;

checked:
	if (ret != LDB_SUCCESS) {
		dsdb_acl_debug(sd, acl_user_token(module),
			       req->op.mod.message->dn,
			       true,
			       10);
		talloc_free(tmp_ctx);
		return ret;
	}

	ret = ldb_request_add_control(req,
		DSDB_CONTROL_PASSWORD_ACL_VALIDATION_OID, false, pav);
	if (ret != LDB_SUCCESS) {
		ldb_debug(ldb_module_get_ctx(module), LDB_DEBUG_ERROR,
			  "Unable to register ACL validation control!\n");
		return ret;
	}
	return LDB_SUCCESS;
}
