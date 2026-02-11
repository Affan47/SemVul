nav_clip_time_search(NAV_CLIP *clip, uint32_t tick, uint32_t *clip_pkt, uint32_t *out_pkt)
{
    if (tick >= clip->out_time) {
        *clip_pkt = clip->end_pkt;
    } else {
        if (clip->cl != NULL) {
            *clip_pkt = clpi_lookup_spn(clip->cl, tick, 1,
               clip->title->pl->play_item[clip->ref].clip[clip->angle].stc_id);
        } else {
            *clip_pkt = clip->start_pkt;
        }
    }
    *out_pkt = clip->pos + *clip_pkt - clip->start_pkt;
}
