mark_context(mrb_state *mrb, struct mrb_context *c)
{
  int i;
  mrb_callinfo *ci;

 start:
  if (c->status == MRB_FIBER_TERMINATED) return;


  mark_context_stack(mrb, c);


  if (c->cibase) {
    for (ci = c->cibase; ci <= c->ci; ci++) {
      mrb_gc_mark(mrb, (struct RBasic*)ci->env);
      mrb_gc_mark(mrb, (struct RBasic*)ci->proc);
      mrb_gc_mark(mrb, (struct RBasic*)ci->target_class);
    }
  }

  for (i=0; i<c->eidx; i++) {
    mrb_gc_mark(mrb, (struct RBasic*)c->ensure[i]);
  }

  mrb_gc_mark(mrb, (struct RBasic*)c->fib);
  if (c->prev) {
    c = c->prev;
    goto start;
  }
}
