ojc_object_nappend(ojcErr err, ojcVal object, const char *key, int klen, ojcVal val) {
    if (bad_object(err, object, "append")) {
	return;
    }
    val->next = 0;
    _ojc_set_key(val, key, klen);
    if (0 == object->members.head) {
	object->members.head = val;
    } else {
	object->members.tail->next = val;
    }
    object->members.tail = val;
}
