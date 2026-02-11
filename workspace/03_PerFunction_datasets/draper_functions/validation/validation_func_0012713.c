newJob(const KUrl::List& src, const KUrl& dest,
                                  CopyJob::CopyMode mode, bool asMethod, JobFlags flags)
    {
        CopyJob *job = new CopyJob(*new CopyJobPrivate(src,dest,mode,asMethod));
        job->setUiDelegate(new JobUiDelegate);
        if (!(flags & HideProgressInfo))
            KIO::getJobTracker()->registerJob(job);
        if (flags & KIO::Overwrite) {
            job->d_func()->m_bOverwriteAllDirs = true;
            job->d_func()->m_bOverwriteAllFiles = true;
        }
        return job;
    }
