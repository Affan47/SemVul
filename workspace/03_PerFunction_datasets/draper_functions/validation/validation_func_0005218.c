_ojc_val_create(ojcValType type) {
    ojcVal	val;

    if (free_vals.head == free_vals.tail) {
	val = (ojcVal)malloc(sizeof(struct _ojcVal));
    } else {
	pthread_mutex_lock(&free_mutex);
	if (free_vals.head == free_vals.tail) {
	    val = (ojcVal)malloc(sizeof(struct _ojcVal));
	} else {
	    val = free_vals.head;
	    free_vals.head = free_vals.head->next;
	}
	pthread_mutex_unlock(&free_mutex);
    }
    val->next = 0;
    val->key_type = STR_NONE;
    val->str_type = STR_NONE;
    val->members.head = 0;
    val->members.tail = 0;
    val->type = type;
    val->expect = NEXT_NONE;

    return val;
}
