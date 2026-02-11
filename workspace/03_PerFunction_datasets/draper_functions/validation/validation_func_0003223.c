schemareload_destructor(Slapi_Task *task)
{
    if (task) {
        task_data *mydata = (task_data *)slapi_task_get_data(task);
        if (mydata) {
            slapi_ch_free_string(&mydata->schemadir);
            slapi_ch_free_string(&mydata->bind_dn);

            slapi_ch_free((void **)&mydata);
        }
    }
}
