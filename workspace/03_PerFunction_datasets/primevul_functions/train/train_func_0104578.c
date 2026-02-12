mirror_wait_for_any_operation(MirrorBlockJob *s, bool active)
{
    MirrorOp *op;

    QTAILQ_FOREACH(op, &s->ops_in_flight, next) {


        if (!op->is_pseudo_op && op->is_in_flight &&
            op->is_active_write == active)
        {
            qemu_co_queue_wait(&op->waiting_requests, NULL);
            return;
        }
    }
    abort();
}
