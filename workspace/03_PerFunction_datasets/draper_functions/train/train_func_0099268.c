fm_folder_dispose(GObject *object)
{
    FmFolder *folder;
    g_return_if_fail(object != NULL);
    g_return_if_fail(FM_IS_FOLDER(object));


    folder = (FmFolder*)object;

    if(folder->dirlist_job)
        free_dirlist_job(folder);

    if(folder->pending_jobs)
    {
        GSList* l;
        for(l = folder->pending_jobs;l;l=l->next)
        {
            FmJob* job = FM_JOB(l->data);
            g_signal_handlers_disconnect_by_func(job, on_file_info_job_finished, folder);
            fm_job_cancel(job);
            g_object_unref(job);
        }
        g_slist_free(folder->pending_jobs);
        folder->pending_jobs = NULL;
    }

    if(folder->mon)
    {
        g_signal_handlers_disconnect_by_func(folder->mon, on_folder_changed, folder);
        g_object_unref(folder->mon);
        folder->mon = NULL;
    }

    G_LOCK(query);
    if(folder->idle_reload_handler)
    {
        g_source_remove(folder->idle_reload_handler);
        folder->idle_reload_handler = 0;
    }

    if(folder->idle_handler)
    {
        g_source_remove(folder->idle_handler);
        folder->idle_handler = 0;
        if(folder->files_to_add)
        {
            g_slist_foreach(folder->files_to_add, (GFunc)fm_path_unref, NULL);
            g_slist_free(folder->files_to_add);
            folder->files_to_add = NULL;
        }
        if(folder->files_to_update)
        {
            g_slist_foreach(folder->files_to_update, (GFunc)fm_path_unref, NULL);
            g_slist_free(folder->files_to_update);
            folder->files_to_update = NULL;
        }
        if(folder->files_to_del)
        {
            g_slist_free(folder->files_to_del);
            folder->files_to_del = NULL;
        }
    }

    if(folder->fs_size_cancellable)
    {
        g_cancellable_cancel(folder->fs_size_cancellable);
        g_object_unref(folder->fs_size_cancellable);
        folder->fs_size_cancellable = NULL;
    }
    G_UNLOCK(query);


    if(folder->dir_path)
    {
        G_LOCK(hash);
        g_hash_table_remove(hash, folder->dir_path);
        G_UNLOCK(hash);
        fm_path_unref(folder->dir_path);
        folder->dir_path = NULL;
    }

    if(folder->dir_fi)
    {
        fm_file_info_unref(folder->dir_fi);
        folder->dir_fi = NULL;
    }

    if(folder->gf)
    {
        g_object_unref(folder->gf);
        folder->gf = NULL;
    }

    if(folder->files)
    {
        fm_file_info_list_unref(folder->files);
        folder->files = NULL;
    }

    (* G_OBJECT_CLASS(fm_folder_parent_class)->dispose)(object);
}
