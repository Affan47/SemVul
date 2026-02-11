tst_traverse(tst_t *p, tst_traverse_cb cb, void *data)
{
    if (!p) return;

    int q_start = 0;
    int q_size = 0;
    int q_max = MAX_TRAVERSE_SIZE;
    tst_t **queue = calloc(sizeof(tst_t *), MAX_TRAVERSE_SIZE);

    check(queue, "Failed to malloc queue for traverse");

    queue[q_start] = p;
    q_size++;

    while(q_size > 0) {
        tst_t *cur = queue[q_start];
        q_start = (q_start + 1) % q_max;
        q_size--;


        if(q_size + 3 > q_max) {
            queue = tst_resize_queue(queue, q_start, q_size, q_max, q_max * 2);
            q_start = 0;
            q_max = q_max * 2;
        }

        if(cur->value) cb(cur->value, data);

        if(cur->low) queue[(q_start + (q_size++)) % q_max] = cur->low;
        if(cur->equal) queue[(q_start + (q_size++)) % q_max] = cur->equal;
        if(cur->high) queue[(q_start + (q_size++)) % q_max] = cur->high;
    }

    free(queue);
    return;

error:
    if(queue) free(queue);
}
