__rb_reserve_next(struct ring_buffer_per_cpu *cpu_buffer,
		  struct rb_event_info *info)
{
	struct ring_buffer_event *event;
	struct buffer_page *tail_page;
	unsigned long tail, write, w;
	bool a_ok;
	bool b_ok;


	tail_page = info->tail_page = READ_ONCE(cpu_buffer->tail_page);

 	w = local_read(&tail_page->write) & RB_WRITE_MASK;
	barrier();
	b_ok = rb_time_read(&cpu_buffer->before_stamp, &info->before);
	a_ok = rb_time_read(&cpu_buffer->write_stamp, &info->after);
	barrier();
	info->ts = rb_time_stamp(cpu_buffer->buffer);

	if ((info->add_timestamp & RB_ADD_STAMP_ABSOLUTE)) {
		info->delta = info->ts;
	} else {


		if (unlikely(!a_ok || !b_ok || (info->before != info->after && w))) {
			info->add_timestamp |= RB_ADD_STAMP_FORCE | RB_ADD_STAMP_EXTEND;
			info->length += RB_LEN_TIME_EXTEND;
		} else {
			info->delta = info->ts - info->after;
			if (unlikely(test_time_stamp(info->delta))) {
				info->add_timestamp |= RB_ADD_STAMP_EXTEND;
				info->length += RB_LEN_TIME_EXTEND;
			}
		}
	}

 	rb_time_set(&cpu_buffer->before_stamp, info->ts);

 	write = local_add_return(info->length, &tail_page->write);


	write &= RB_WRITE_MASK;

	tail = write - info->length;


	if (unlikely(write > BUF_PAGE_SIZE)) {

		b_ok = rb_time_read(&cpu_buffer->before_stamp, &info->before);
		a_ok = rb_time_read(&cpu_buffer->write_stamp, &info->after);
		if (a_ok && b_ok && info->before != info->after)
			(void)rb_time_cmpxchg(&cpu_buffer->before_stamp,
					      info->before, info->after);
		if (a_ok && b_ok)
			check_buffer(cpu_buffer, info, CHECK_FULL_PAGE);
		return rb_move_tail(cpu_buffer, tail, info);
	}

	if (likely(tail == w)) {
		u64 save_before;
		bool s_ok;


 		rb_time_set(&cpu_buffer->write_stamp, info->ts);
		barrier();
 		s_ok = rb_time_read(&cpu_buffer->before_stamp, &save_before);
		RB_WARN_ON(cpu_buffer, !s_ok);
		if (likely(!(info->add_timestamp &
			     (RB_ADD_STAMP_FORCE | RB_ADD_STAMP_ABSOLUTE))))

			info->delta = info->ts - info->after;
		else

			info->delta = info->ts;
		barrier();
		check_buffer(cpu_buffer, info, tail);
		if (unlikely(info->ts != save_before)) {


			a_ok = rb_time_read(&cpu_buffer->write_stamp, &info->after);
			RB_WARN_ON(cpu_buffer, !a_ok);


			if (save_before > info->after) {


				(void)rb_time_cmpxchg(&cpu_buffer->write_stamp,
						      info->after, save_before);
			}
		}
	} else {
		u64 ts;

		a_ok = rb_time_read(&cpu_buffer->write_stamp, &info->after);

		RB_WARN_ON(cpu_buffer, !a_ok);
		ts = rb_time_stamp(cpu_buffer->buffer);
		barrier();
 		if (write == (local_read(&tail_page->write) & RB_WRITE_MASK) &&
		    info->after < ts &&
		    rb_time_cmpxchg(&cpu_buffer->write_stamp,
				    info->after, ts)) {

			info->delta = ts - info->after;
		} else {


			info->delta = 0;
		}
		info->ts = ts;
		info->add_timestamp &= ~RB_ADD_STAMP_FORCE;
	}


	if (unlikely(!tail && !(info->add_timestamp &
				(RB_ADD_STAMP_FORCE | RB_ADD_STAMP_ABSOLUTE))))
		info->delta = 0;


	event = __rb_page_index(tail_page, tail);
	rb_update_event(cpu_buffer, event, info);

	local_inc(&tail_page->entries);


	if (unlikely(!tail))
		tail_page->page->time_stamp = info->ts;


	local_add(info->length, &cpu_buffer->entries_bytes);

	return event;
}
