execute(const QString &helperID) const
{

    if (!isValid()) {
        return ActionReply::InvalidActionReply;
    }


    if (BackendsManager::authBackend()->capabilities() & KAuth::AuthBackend::AuthorizeFromClientCapability) {
        if (BackendsManager::authBackend()->capabilities() & KAuth::AuthBackend::PreAuthActionCapability) {
            BackendsManager::authBackend()->preAuthAction(d->name, d->parent);
        }

        AuthStatus s = BackendsManager::authBackend()->authorizeAction(d->name);


        switch (s) {
        case Denied:
            return ActionReply::AuthorizationDeniedReply;
        case Invalid:
            return ActionReply::InvalidActionReply;
        case UserCancelled:
            return ActionReply::UserCancelledReply;
        default:
            break;
        }
    } else if (BackendsManager::authBackend()->capabilities() & KAuth::AuthBackend::AuthorizeFromHelperCapability) {

        if (!d->async && !hasHelper()) {

            switch (authorize()) {
            case Denied:
                return ActionReply::AuthorizationDeniedReply;
            case Invalid:
                return ActionReply::InvalidActionReply;
            case UserCancelled:
                return ActionReply::UserCancelledReply;
            default:
                break;
            }
        }
    } else {

        return ActionReply::InvalidActionReply;
    }

    if (d->async) {
        if (!hasHelper()) {

            return ActionReply::InvalidActionReply;
        }

        return executeActions(QList<Action>() << *this, NULL, helperID) ?
            ActionReply::SuccessReply : ActionReply::AuthorizationDeniedReply;
    } else {
        if (hasHelper()) {

            if (BackendsManager::authBackend()->capabilities() & KAuth::AuthBackend::PreAuthActionCapability) {
                BackendsManager::authBackend()->preAuthAction(d->name, d->parent);
            }

            return BackendsManager::helperProxy()->executeAction(d->name, helperID, d->args);
        } else {
            return ActionReply::SuccessReply;
        }
    }
}
