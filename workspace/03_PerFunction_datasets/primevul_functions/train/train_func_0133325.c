static enum rule_result http_res_get_intercept_rule(struct proxy *px, struct list *def_rules,
						    struct list *rules, struct stream *s)
{
	struct session *sess = strm_sess(s);
	struct http_txn *txn = s->txn;
	struct act_rule *rule;
	enum rule_result rule_ret = HTTP_RULE_RES_CONT;
	int act_opts = 0;


	if (s->current_rule) {
		rule = s->current_rule;
		s->current_rule = NULL;
		if (s->current_rule_list == rules || (def_rules && s->current_rule_list == def_rules))
			goto resume_execution;
	}
	s->current_rule_list = ((!def_rules || s->current_rule_list == def_rules) ? rules : def_rules);

  restart:


	txn->rsp.flags &= ~HTTP_MSGF_SOFT_RW;

	list_for_each_entry(rule, s->current_rule_list, list) {

		if (rule->cond) {
			int ret;

			ret = acl_exec_cond(rule->cond, px, sess, s, SMP_OPT_DIR_RES|SMP_OPT_FINAL);
			ret = acl_pass(ret);

			if (rule->cond->pol == ACL_COND_UNLESS)
				ret = !ret;

			if (!ret)
				continue;
		}

		act_opts |= ACT_OPT_FIRST;
resume_execution:
		if (rule->kw->flags & KWF_EXPERIMENTAL)
			mark_tainted(TAINTED_ACTION_EXP_EXECUTED);


		if (rule->action_ptr) {
			if ((s->req.flags & CF_READ_ERROR) ||
			    ((s->req.flags & (CF_SHUTR|CF_READ_NULL)) &&
			     (px->options & PR_O_ABRT_CLOSE)))
				act_opts |= ACT_OPT_FINAL;

			switch (rule->action_ptr(rule, px, sess, s, act_opts)) {
				case ACT_RET_CONT:
					break;
				case ACT_RET_STOP:
					rule_ret = HTTP_RULE_RES_STOP;
					goto end;
				case ACT_RET_YIELD:
					s->current_rule = rule;
					rule_ret = HTTP_RULE_RES_YIELD;
					goto end;
				case ACT_RET_ERR:
					rule_ret = HTTP_RULE_RES_ERROR;
					goto end;
				case ACT_RET_DONE:
					rule_ret = HTTP_RULE_RES_DONE;
					goto end;
				case ACT_RET_DENY:
					if (txn->status == -1)
						txn->status = 502;
					rule_ret = HTTP_RULE_RES_DENY;
					goto end;
				case ACT_RET_ABRT:
					rule_ret = HTTP_RULE_RES_ABRT;
					goto end;
				case ACT_RET_INV:
					rule_ret = HTTP_RULE_RES_BADREQ;
					goto end;
			}
			continue;
		}


		switch (rule->action) {
			case ACT_ACTION_ALLOW:
				rule_ret = HTTP_RULE_RES_STOP;
				goto end;

			case ACT_ACTION_DENY:
				txn->status = rule->arg.http_reply->status;
				txn->http_reply = rule->arg.http_reply;
				rule_ret = HTTP_RULE_RES_DENY;
				goto end;

			case ACT_HTTP_REDIR: {
				int ret = http_apply_redirect_rule(rule->arg.redir, s, txn);

				if (ret == 2)
					break;

				rule_ret = ret ? HTTP_RULE_RES_ABRT : HTTP_RULE_RES_ERROR;
				goto end;
			}

			default:
				break;
		}
	}

	if (def_rules && s->current_rule_list == def_rules) {
		s->current_rule_list = rules;
		goto restart;
	}

  end:

	if (rule_ret != HTTP_RULE_RES_YIELD)
		txn->rsp.flags &= ~HTTP_MSGF_SOFT_RW;


	return rule_ret;
}
