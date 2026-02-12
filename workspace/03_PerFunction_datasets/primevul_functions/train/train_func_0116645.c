void manager_clear_jobs(Manager *m) {
        Job *j;

        assert(m);

        while ((j = hashmap_first(m->jobs)))

                job_finish_and_invalidate(j, JOB_CANCELED, false);
}
