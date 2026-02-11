dump_counters_value (Counter *counter, const char *key_format, const char *key, void *value)
{
	char format[32];

	if (value == NULL) {
		snprintf (format, sizeof (format), "%s : %%s\n", key_format);
		fprintf (outfile, format, key, "<null>");
	} else {
		switch (counter->type) {
		case MONO_COUNTER_INT:
#if SIZEOF_VOID_P == 4
		case MONO_COUNTER_WORD:
#endif
			snprintf (format, sizeof (format), "%s : %%d\n", key_format);
			fprintf (outfile, format, key, *(int32_t*)value);
			break;
		case MONO_COUNTER_UINT:
			snprintf (format, sizeof (format), "%s : %%u\n", key_format);
			fprintf (outfile, format, key, *(uint32_t*)value);
			break;
		case MONO_COUNTER_LONG:
#if SIZEOF_VOID_P == 8
		case MONO_COUNTER_WORD:
#endif
		case MONO_COUNTER_TIME_INTERVAL:
			if (counter->type == MONO_COUNTER_LONG && counter->unit == MONO_COUNTER_TIME) {
				snprintf (format, sizeof (format), "%s : %%0.3fms\n", key_format);
				fprintf (outfile, format, key, (double)*(int64_t*)value / 10000.0);
			} else if (counter->type == MONO_COUNTER_TIME_INTERVAL) {
				snprintf (format, sizeof (format), "%s : %%0.3fms\n", key_format);
				fprintf (outfile, format, key, (double)*(int64_t*)value / 1000.0);
			} else {
				snprintf (format, sizeof (format), "%s : %%u\n", key_format);
				fprintf (outfile, format, key, *(int64_t*)value);
			}
			break;
		case MONO_COUNTER_ULONG:
			snprintf (format, sizeof (format), "%s : %%llu\n", key_format);
			fprintf (outfile, format, key, *(uint64_t*)value);
			break;
		case MONO_COUNTER_DOUBLE:
			snprintf (format, sizeof (format), "%s : %%f\n", key_format);
			fprintf (outfile, format, key, *(double*)value);
			break;
		case MONO_COUNTER_STRING:
			snprintf (format, sizeof (format), "%s : %%s\n", key_format);
			fprintf (outfile, format, key, *(char*)value);
			break;
		}
	}
}
