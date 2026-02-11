stack_save(jq_state *jq, uint16_t* retaddr){
  struct forkpoint* fork = forkable_stack_push(&jq->fork_stk, sizeof(struct forkpoint));
  forkable_stack_save(&jq->data_stk, &fork->saved_data_stack);
  forkable_stack_save(&jq->frame_stk, &fork->saved_call_stack);
  fork->path_len =
    jv_get_kind(jq->path) == JV_KIND_ARRAY ? jv_array_length(jv_copy(jq->path)) : 0;
  fork->subexp_nest = jq->subexp_nest;
  fork->return_address = retaddr;
}
