bd_chapter_pos(BLURAY *bd, unsigned chapter)
{
    uint32_t clip_pkt, out_pkt;
    int64_t ret = -1;

    bd_mutex_lock(&bd->mutex);

    if (bd->title &&
        chapter < bd->title->chap_list.count) {


        nav_chapter_search(bd->title, chapter, &clip_pkt, &out_pkt);
        ret = (int64_t)out_pkt * 192;
    }

    bd_mutex_unlock(&bd->mutex);

    return ret;
}
