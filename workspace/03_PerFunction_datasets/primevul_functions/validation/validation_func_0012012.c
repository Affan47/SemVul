lyxml_unlink_elem(struct ly_ctx *ctx, struct lyxml_elem *elem, int copy_ns)
{
    struct lyxml_elem *parent, *first;

    if (!elem) {
        return;
    }


    parent = elem->parent;


    if (parent) {
        if (parent->child == elem) {


            parent->child = elem->next;
        }

        elem->parent = NULL;
    }

    if (copy_ns < 2) {
        lyxml_correct_elem_ns(ctx, elem, parent, copy_ns, 1);
    }


    if (elem->prev == elem) {

        return;
    }
    if (elem->next) {
        elem->next->prev = elem->prev;
    } else {

        if (parent) {
            first = parent->child;
        } else {
            first = elem;
            while (first->prev->next) {
                first = first->prev;
            }
        }
        first->prev = elem->prev;
    }
    if (elem->prev->next) {
        elem->prev->next = elem->next;
    }


    elem->next = NULL;
    elem->prev = elem;
}
