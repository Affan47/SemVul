ChangeLedFeedback(ClientPtr client, DeviceIntPtr dev, long unsigned int mask,
                  LedFeedbackPtr l, xLedFeedbackCtl * f)
{
    LedCtrl lctrl;

    if (client->swapped) {
        swaps(&f->length);
        swapl(&f->led_values);
        swapl(&f->led_mask);
    }

    f->led_mask &= l->ctrl.led_mask;
    f->led_values &= l->ctrl.led_mask;
    if (mask & DvLed) {
        lctrl.led_mask = f->led_mask;
        lctrl.led_values = f->led_values;
        (*l->CtrlProc) (dev, &lctrl);
        l->ctrl.led_values &= ~(f->led_mask);
        l->ctrl.led_values |= (f->led_mask & f->led_values);
    }

    return Success;
}
