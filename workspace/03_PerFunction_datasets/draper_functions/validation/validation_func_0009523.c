run(const QueryMatch &match)
{
    if (!match.isEnabled()) {
        return;
    }


    AbstractRunner *runner = match.runner();

    foreach (FindMatchesJob *job, d->searchJobs) {
        if (job->runner() == runner && !job->isFinished()) {
            kDebug() << "deferred run";
            d->deferredRun = match;
            return;
        }
    }

    if (d->deferredRun.isValid()) {
        d->deferredRun = QueryMatch(0);
    }

    d->context.run(match);
}
