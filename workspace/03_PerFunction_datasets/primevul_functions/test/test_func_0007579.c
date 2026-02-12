static int find_prev_closest_index(AVStream *st,
                                   AVIndexEntry *e_old,
                                   int nb_old,
                                   MOVCtts* ctts_data,
                                   int64_t ctts_count,
                                   int64_t timestamp_pts,
                                   int flag,
                                   int64_t* index,
                                   int64_t* ctts_index,
                                   int64_t* ctts_sample)
{
    MOVStreamContext *msc = st->priv_data;
    FFStream *const sti = ffstream(st);
    AVIndexEntry *e_keep = sti->index_entries;
    int nb_keep = sti->nb_index_entries;
    int64_t i = 0;
    int64_t index_ctts_count;

    av_assert0(index);


    if (msc->dts_shift > 0) {
        timestamp_pts -= msc->dts_shift;
    }

    sti->index_entries    = e_old;
    sti->nb_index_entries = nb_old;
    *index = av_index_search_timestamp(st, timestamp_pts, flag | AVSEEK_FLAG_BACKWARD);


    if (*index >= 0) {
        for (i = *index; i > 0 && e_old[i].timestamp == e_old[i - 1].timestamp;
             i--) {
            if ((flag & AVSEEK_FLAG_ANY) ||
                (e_old[i - 1].flags & AVINDEX_KEYFRAME)) {
                *index = i - 1;
            }
        }
    }


    if (ctts_data && *index >= 0) {
        av_assert0(ctts_index);
        av_assert0(ctts_sample);

        *ctts_index = 0;
        *ctts_sample = 0;
        for (index_ctts_count = 0; index_ctts_count < *index; index_ctts_count++) {
            if (*ctts_index < ctts_count) {
                (*ctts_sample)++;
                if (ctts_data[*ctts_index].count == *ctts_sample) {
                    (*ctts_index)++;
                    *ctts_sample = 0;
                }
            }
        }

        while (*index >= 0 && (*ctts_index) >= 0 && (*ctts_index) < ctts_count) {


            if ((e_old[*index].timestamp + ctts_data[*ctts_index].duration) <= timestamp_pts &&
                (e_old[*index].flags & AVINDEX_KEYFRAME)) {
                break;
            }

            (*index)--;
            if (*ctts_sample == 0) {
                (*ctts_index)--;
                if (*ctts_index >= 0)
                  *ctts_sample = ctts_data[*ctts_index].count - 1;
            } else {
                (*ctts_sample)--;
            }
        }
    }


    sti->index_entries    = e_keep;
    sti->nb_index_entries = nb_keep;
    return *index >= 0 ? 0 : -1;
}
