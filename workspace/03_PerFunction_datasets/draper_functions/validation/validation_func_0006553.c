msg_tech_hash(const void *obj, const int flags)
{
	struct ast_msg_tech_holder *tech_holder = (struct ast_msg_tech_holder *) obj;
	int res = 0;

	ast_rwlock_rdlock(&tech_holder->tech_lock);
	if (tech_holder->tech) {
		res = ast_str_case_hash(tech_holder->tech->name);
	}
	ast_rwlock_unlock(&tech_holder->tech_lock);

	return res;
}
