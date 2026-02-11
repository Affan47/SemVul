bt_ctf_field_integer_destroy(struct bt_ctf_field *field)
{
	struct bt_ctf_field_integer *integer;

	if (!field) {
		return;
	}

	integer = container_of(field, struct bt_ctf_field_integer, parent);
	g_free(integer);
}
