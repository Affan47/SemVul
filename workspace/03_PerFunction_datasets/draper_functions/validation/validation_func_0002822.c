add_event_to_list(struct eventlist *events, struct ast_calendar_event *event, time_t start, time_t end)
{
	struct evententry *entry, *iter;
	int event_startdiff = abs(start - event->start);
	int event_enddiff = abs(end - event->end);
	int i = 0;

	if (!(entry = ast_calloc(1, sizeof(*entry)))) {
		ast_log(LOG_ERROR, "Unable to allocate memory for event list\n");
		return -1;
	}

	entry->event = event;
	ao2_ref(event, +1);

	if (start == end) {
		AST_LIST_TRAVERSE_SAFE_BEGIN(events, iter, list) {
			int startdiff = abs(iter->event->start - start);

			ast_debug(10, "Comparing %s with startdiff %d to %s with startdiff %d\n", event->summary, event_startdiff, iter->event->summary, startdiff);
			++i;
			if (startdiff > event_startdiff) {
				AST_LIST_INSERT_BEFORE_CURRENT(entry, list);
				return i;
			}
			if (startdiff == event_startdiff) {
				int enddiff = abs(iter->event->end - end);

				if (enddiff > event_enddiff) {
					AST_LIST_INSERT_BEFORE_CURRENT(entry, list);
					return i;
				}
				if (event_startdiff == enddiff) {
					if (strcmp(event->uid, iter->event->uid) < 0) {
						AST_LIST_INSERT_BEFORE_CURRENT(entry, list);
						return i;
					}
				}
			}
		}
		AST_LIST_TRAVERSE_SAFE_END;

		AST_LIST_INSERT_TAIL(events, entry, list);

		return i;
	}

	AST_LIST_TRAVERSE_SAFE_BEGIN(events, iter, list) {
		++i;
		if (iter->event->start > event->start) {
			AST_LIST_INSERT_BEFORE_CURRENT(entry, list);
			return i;
		}

		if (iter->event->start == event->start) {
			if ((iter->event->end - iter->event->start) == (event->end - event->start)) {
				if (strcmp(event->uid, iter->event->uid) < 0) {
					AST_LIST_INSERT_BEFORE_CURRENT(entry, list);
					return i;
				}
			}
			if ((iter->event->end - iter->event->start) < (event->end - event->start)) {
				AST_LIST_INSERT_BEFORE_CURRENT(entry, list);
				return i;
			}
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;

	AST_LIST_INSERT_TAIL(events, entry, list);

	return i;
}
