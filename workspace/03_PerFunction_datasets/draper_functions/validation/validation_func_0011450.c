ompi_coll_libnbc_iscatter_inter(void* sendbuf, int sendcount, MPI_Datatype sendtype,
                                    void* recvbuf, int recvcount, MPI_Datatype recvtype, int root,
                                    struct ompi_communicator_t *comm, ompi_request_t ** request,
                                    struct mca_coll_base_module_2_0_0_t *module) {
    int rank, res, i, rsize;
    MPI_Aint sndext;
    NBC_Schedule *schedule;
    char *sbuf;
    NBC_Handle *handle;
    ompi_coll_libnbc_request_t **coll_req = (ompi_coll_libnbc_request_t**) request;
    ompi_coll_libnbc_module_t *libnbc_module = (ompi_coll_libnbc_module_t*) module;

    res = NBC_Init_handle(comm, coll_req, libnbc_module);
    if(res != NBC_OK) { printf("Error in NBC_Init_handle(%i)\n", res); return res; }
    handle = (*coll_req);
    res = MPI_Comm_rank(comm, &rank);
    if (MPI_SUCCESS != res) { printf("MPI Error in MPI_Comm_rank() (%i)\n", res); return res; }
    res = MPI_Type_extent(sendtype, &sndext);
    if (MPI_SUCCESS != res) { printf("MPI Error in MPI_Type_extent() (%i)\n", res); return res; }
    res = MPI_Comm_remote_size (comm, &rsize);
    if (MPI_SUCCESS != res) { printf("MPI Error in MPI_Comm_remote_size() (%i)\n", res); return res; }

    handle->tmpbuf = NULL;

    schedule = (NBC_Schedule*)malloc(sizeof(NBC_Schedule));
    if (NULL == schedule) { printf("Error in malloc()\n"); return res; }

    res = NBC_Sched_create(schedule);
    if(res != NBC_OK) { printf("Error in NBC_Sched_create (%i)\n", res); return res; }


    if (MPI_ROOT != root && MPI_PROC_NULL != root) {

        res = NBC_Sched_recv(recvbuf, false, recvcount, recvtype, root, schedule);
        if (NBC_OK != res) { printf("Error in NBC_Sched_recv() (%i)\n", res); return res; }
    } else if (MPI_ROOT == root) {
        for (i = 0 ; i < rsize ; ++i) {
            sbuf = ((char *)sendbuf) + (i * sendcount * sndext);

            res = NBC_Sched_send(sbuf, false, sendcount, sendtype, i, schedule);
            if (NBC_OK != res) { printf("Error in NBC_Sched_send() (%i)\n", res); return res; }
        }
    }

    res = NBC_Sched_commit(schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_commit() (%i)\n", res); return res; }

    res = NBC_Start(handle, schedule);
    if (NBC_OK != res) { printf("Error in NBC_Start() (%i)\n", res); return res; }

    return NBC_OK;
}
