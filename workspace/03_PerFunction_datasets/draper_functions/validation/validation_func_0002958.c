ff_nut_add_sp(NUTContext *nut, int64_t pos, int64_t back_ptr, int64_t ts){
    Syncpoint *sp= av_mallocz(sizeof(Syncpoint));
    struct AVTreeNode *node= av_mallocz(av_tree_node_size);

    sp->pos= pos;
    sp->back_ptr= back_ptr;
    sp->ts= ts;
    av_tree_insert(&nut->syncpoints, sp, ff_nut_sp_pos_cmp, &node);
    if(node){
        av_free(sp);
        av_free(node);
    }
}
