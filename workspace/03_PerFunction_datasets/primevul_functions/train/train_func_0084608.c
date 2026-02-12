static void *_timeout_fn(void *arg)
{
    struct uc_struct *uc = arg;
    int64_t current_time = get_clock();

    do {
        usleep(TIMEOUT_STEP);

        if (uc->emulation_done) {
            break;
        }
    } while ((uint64_t)(get_clock() - current_time) < uc->timeout);


    if (!uc->emulation_done) {
        uc->timed_out = true;

        uc_emu_stop(uc);
    }

    return NULL;
}
