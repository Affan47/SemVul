get_sssas(DBusMessage *rep, int msgid)
{
	int ret, i;
	char *s1, *s2, *s3, **as;
	ret = cm_tdbusm_get_sssas(rep, NULL, &s1, &s2, &s3, &as);
	if (ret == 0) {
		printf("Message %d - s:%s,s:%s,s:%s,[", msgid, s1, s2, s3);
		for (i = 0; (as != NULL) && (as[i] != NULL); i++) {
			printf("%ss:%s", i > 0 ? "," : "", as[i]);
		}
		printf("]\n");
	}
	return ret;
}
