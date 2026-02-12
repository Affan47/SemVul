void AbstractWebApplication::increaseFailedAttempts()
{
    const int nb_fail = clientFailedAttempts_.value(env_.clientAddress, 0) + 1;

    clientFailedAttempts_[env_.clientAddress] = nb_fail;
    if (nb_fail == MAX_AUTH_FAILED_ATTEMPTS) {


        UnbanTimer* ubantimer = new UnbanTimer(env_.clientAddress, this);
        connect(ubantimer, SIGNAL(timeout()), SLOT(UnbanTimerEvent()));
        ubantimer->start();
    }
}
