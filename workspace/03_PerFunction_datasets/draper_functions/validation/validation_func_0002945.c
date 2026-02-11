bt_ctf_clock_put(struct bt_ctf_clock *clock)
{
	if (!clock) {
		return;
	}

	bt_ctf_ref_put(&clock->ref_count, bt_ctf_clock_destroy);
}
