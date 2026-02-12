int generic_write_stats(int curr, int use_tm_start, int use_tm_end, int reset,
			long *cnt, void *parm, struct tm *rectime,
			struct tm *loctime, int reset_cd, unsigned int act_id)
{
	int i;
	unsigned long long dt, itv;
	char cur_date[TIMESTAMP_LEN], cur_time[TIMESTAMP_LEN], *pre = NULL;
	static int cross_day = FALSE;

	if (reset_cd) {


		cross_day = 0;
	}


	if (!next_slice(record_hdr[2].uptime_cs, record_hdr[curr].uptime_cs,
			reset, interval))

		return 0;


	if (use_tm_start && record_hdr[!curr].ust_time &&
	    (record_hdr[curr].ust_time > record_hdr[!curr].ust_time) &&
	    (record_hdr[curr].hour < record_hdr[!curr].hour)) {
		cross_day = TRUE;
	}

	if (cross_day) {


		loctime->tm_hour += 24;
	}


	if (use_tm_start && (datecmp(loctime, &tm_start) < 0))

		return 0;


	get_itv_value(&record_hdr[curr], &record_hdr[!curr], &itv);


	if (use_tm_end && (datecmp(loctime, &tm_end) > 0)) {

		*cnt = 0;
		return 0;
	}

	dt = itv / 100;

	if ((itv % 100) >= 50) {
		dt++;
	}


	set_record_timestamp_string(flags, &record_hdr[curr],
				    cur_date, cur_time, TIMESTAMP_LEN, rectime);

	if (*fmt[f_position]->f_timestamp) {
		pre = (char *) (*fmt[f_position]->f_timestamp)(parm, F_BEGIN, cur_date, cur_time,
							       dt, &file_hdr, flags);
	}


	for (i = 0; i < NR_ACT; i++) {

		if ((act_id != ALL_ACTIVITIES) && (act[i]->id != act_id))
			continue;

		if ((TEST_MARKUP(fmt[f_position]->options) && CLOSE_MARKUP(act[i]->options)) ||
		    (IS_SELECTED(act[i]->options) && (act[i]->nr > 0))) {

			if (format == F_JSON_OUTPUT) {

				int *tab = (int *) parm;

				if (IS_SELECTED(act[i]->options) && (act[i]->nr > 0)) {

					if (*fmt[f_position]->f_timestamp) {
						(*fmt[f_position]->f_timestamp)(tab, F_MAIN, cur_date, cur_time,
										dt, &file_hdr, flags);
					}
				}
				(*act[i]->f_json_print)(act[i], curr, *tab, itv);
			}

			else if (format == F_XML_OUTPUT) {

				int *tab = (int *) parm;

				(*act[i]->f_xml_print)(act[i], curr, *tab, itv);
			}

			else if (format == F_SVG_OUTPUT) {

				struct svg_parm *svg_p = (struct svg_parm *) parm;

				svg_p->dt = (unsigned long) dt;
				(*act[i]->f_svg_print)(act[i], curr, F_MAIN, svg_p, itv, &record_hdr[curr]);
			}

			else if (format == F_RAW_OUTPUT) {

				if (DISPLAY_DEBUG_MODE(flags)) {
					printf("# %s: %d/%d (%d)\n", act[i]->name,
					       act[i]->nr[curr], act[i]->nr_allocated, act[i]->nr_ini);
				}

				(*act[i]->f_raw_print)(act[i], pre, curr);
			}

			else {

				(*act[i]->f_render)(act[i], (format == F_DB_OUTPUT), pre, curr, itv);
			}
		}
	}

	if (*fmt[f_position]->f_timestamp) {
		(*fmt[f_position]->f_timestamp)(parm, F_END, cur_date, cur_time,
						dt, &file_hdr, flags);
	}

	return 1;
}
