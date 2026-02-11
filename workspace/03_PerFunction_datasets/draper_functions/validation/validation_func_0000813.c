new_job(int num_resources) {
    job_t job;
    int i;

    if (!(job = (job_t)malloc(sizeof(struct job_s)))) {
        fprintf(stderr, "Insufficient memory to allocate job!\n");
        exit(1);
    }

    if (!(job->unit_rigid_requirements = calloc(num_resources,
        sizeof(double)))) {
        fprintf(stderr, "Insufficient memory to allocate job unit rigid_requirements!\n");
        exit(1);
    }

    if (!(job->unit_fluid_needs = calloc(num_resources, sizeof(double)))) {
        fprintf(stderr, "Insufficient memory to allocate job unit fluid_needs!\n");
        exit(1);
    }

    if (!(job->actual_unit_fluid_needs = calloc(num_resources,
        sizeof(double)))) {
        fprintf(stderr, "Insufficient memory to allocate actual job unit fluid_needs!\n");
        exit(1);
    }

    if (!(job->total_rigid_requirements = calloc(num_resources,
        sizeof(double)))) {
        fprintf(stderr, "Insufficient memory to allocate job total rigid_requirements!\n");
        exit(1);
    }

    if (!(job->total_fluid_needs = calloc(num_resources, sizeof(double)))) {
        fprintf(stderr, "Insufficient memory to allocate job total fluid_needs!\n");
        exit(1);
    }

    if (!(job->actual_total_fluid_needs = calloc(num_resources,
        sizeof(double)))) {
        fprintf(stderr, "Insufficient memory to allocate actual job total fluid_needs!\n");
        exit(1);
    }

    return job;
}
