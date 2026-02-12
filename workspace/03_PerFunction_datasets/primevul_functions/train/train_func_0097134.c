long long streamEstimateDistanceFromFirstEverEntry(stream *s, streamID *id) {

    if (!s->entries_added) {
        return 0;
    }


    if (!s->length && streamCompareID(id,&s->last_id) < 1) {
        return s->entries_added;
    }

    int cmp_last = streamCompareID(id,&s->last_id);
    if (cmp_last == 0) {

        return s->entries_added;
    } else if (cmp_last > 0) {

        return SCG_INVALID_ENTRIES_READ;
    }

    int cmp_id_first = streamCompareID(id,&s->first_id);
    int cmp_xdel_first = streamCompareID(&s->max_deleted_entry_id,&s->first_id);
    if (streamIDEqZero(&s->max_deleted_entry_id) || cmp_xdel_first < 0) {

        if (cmp_id_first < 0) {

            return s->entries_added - s->length;
        } else if (cmp_id_first == 0) {

            return s->entries_added - s->length + 1;
        }
    }


    return SCG_INVALID_ENTRIES_READ;
}
