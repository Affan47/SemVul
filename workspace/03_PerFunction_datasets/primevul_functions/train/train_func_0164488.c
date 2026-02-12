static void enqueue_hrtimer(struct hrtimer *timer,
			    struct hrtimer_clock_base *base, int reprogram)
{
	struct rb_node **link = &base->active.rb_node;
	struct rb_node *parent = NULL;
	struct hrtimer *entry;


	while (*link) {
		parent = *link;
		entry = rb_entry(parent, struct hrtimer, node);


		if (timer->expires.tv64 < entry->expires.tv64)
			link = &(*link)->rb_left;
		else
			link = &(*link)->rb_right;
	}


	if (!base->first || timer->expires.tv64 <
	    rb_entry(base->first, struct hrtimer, node)->expires.tv64) {


		if (reprogram && hrtimer_enqueue_reprogram(timer, base))
			return;

		base->first = &timer->node;
	}

	rb_link_node(&timer->node, parent, link);
	rb_insert_color(&timer->node, &base->active);


	timer->state |= HRTIMER_STATE_ENQUEUED;
}
