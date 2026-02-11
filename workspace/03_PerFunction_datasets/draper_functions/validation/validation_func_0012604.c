afp_server_remove(struct afp_server *s)
{

	struct dsi_request * p;
	struct afp_server *s2;
	for (p=s->command_requests;p;p=p->next) {
		pthread_cond_signal(&p->condition_cond);
	}

	if (s==server_base) {
		server_base=s->next;
		afp_free_server(&s);
		goto out;
	}

	for (s2=server_base;s2;s2=s2->next) {
		if (s==s2->next) {
			s2->next=s->next;
			afp_free_server(&s);
			goto out;
		}
	}
	return -1;
out:
	return 0;

}
