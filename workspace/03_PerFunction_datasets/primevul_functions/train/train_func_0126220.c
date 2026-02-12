bool unit_job_is_applicable(Unit *u, JobType j) {
        assert(u);
        assert(j >= 0 && j < _JOB_TYPE_MAX);

        switch (j) {

        case JOB_VERIFY_ACTIVE:
        case JOB_START:
        case JOB_NOP:


                return true;

        case JOB_STOP:


                return !u->perpetual;

        case JOB_RESTART:
        case JOB_TRY_RESTART:
                return unit_can_stop(u) && unit_can_start(u);

        case JOB_RELOAD:
        case JOB_TRY_RELOAD:
                return unit_can_reload(u);

        case JOB_RELOAD_OR_START:
                return unit_can_reload(u) && unit_can_start(u);

        default:
                assert_not_reached("Invalid job type");
        }
}
