ap_message_find_float(ap_message_t *msg, char *key_id)
{
	ap_key_t *key;

	if ((key = ap_message_find_key(msg, key_id, KTYPE_FLOAT))) {
		return ((float*)key->data);
	}
	return NULL;
}
