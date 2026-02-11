get_task(RESULT* rp) {
    ACTIVE_TASK *atp = lookup_active_task_by_result(rp);
    if (!atp) {
        atp = new ACTIVE_TASK;
        int retval = atp->get_free_slot(rp);
        if (retval) {
            delete atp;
            return NULL;
        }
        atp->init(rp);
        active_tasks.active_tasks.push_back(atp);
    }
    return atp;
}
