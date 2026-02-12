static void hid_pointer_sync(DeviceState *dev)
{
    HIDState *hs = (HIDState *)dev;
    HIDPointerEvent *prev, *curr, *next;
    bool event_compression = false;

    if (hs->n == QUEUE_LENGTH-1) {


        return;
    }

    prev = &hs->ptr.queue[(hs->head + hs->n - 1) & QUEUE_MASK];
    curr = &hs->ptr.queue[(hs->head + hs->n) & QUEUE_MASK];
    next = &hs->ptr.queue[(hs->head + hs->n + 1) & QUEUE_MASK];

    if (hs->n > 0) {


        if (curr->buttons_state == prev->buttons_state) {
            event_compression = true;
        }
    }

    if (event_compression) {

        if (hs->kind == HID_MOUSE) {
            prev->xdx += curr->xdx;
            curr->xdx = 0;
            prev->ydy += curr->ydy;
            curr->ydy = 0;
        } else {
            prev->xdx = curr->xdx;
            prev->ydy = curr->ydy;
        }
        prev->dz += curr->dz;
        curr->dz = 0;
    } else {

        if (hs->kind == HID_MOUSE) {
            next->xdx = 0;
            next->ydy = 0;
        } else {
            next->xdx = curr->xdx;
            next->ydy = curr->ydy;
        }
        next->dz = 0;
        next->buttons_state = curr->buttons_state;

        hs->n++;
        hs->event(hs);
    }
}
