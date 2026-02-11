finished(KJob *job)
{
    if (!d->progressJobView.contains(job)) {
        return;
    }

    org::kde::JobViewV2 *jobView = d->progressJobView.take(job);

    if (job->error()) {
        jobView->terminate(job->errorText());
    } else {
        jobView->terminate(QString());
    }
}
