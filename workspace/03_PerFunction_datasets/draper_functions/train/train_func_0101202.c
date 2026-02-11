_cx_deque_sorted(const cx_deque *deque, cx_compare_func compare)
{

    cxsize i = 0;

    for (i = 0; i < deque->size - 1; ++i) {

        register cxsize current = deque->front + i;

        if (compare(deque->members[current], deque->members[current + 1]) > 0) {
            return 0;
        }

    }

    return 1;

}
