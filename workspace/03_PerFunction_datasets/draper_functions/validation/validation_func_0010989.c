gw_check_claim_area(void *p, const char *filename, long lineno,
                          const char *function)
{
    struct area *area;


    if (p == NULL)
        return NULL;

    lock();
    area = find_area(p);
    if (!area) {
        unlock();
        panic(0, "Claim_area called on non-allocated area");
    }

    area->claimer.filename = filename;
    area->claimer.lineno = lineno;
    area->claimer.function = function;
    unlock();


    return p;
}
