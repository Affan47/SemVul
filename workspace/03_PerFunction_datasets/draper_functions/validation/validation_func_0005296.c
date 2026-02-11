startRequest(QContactAbstractRequest* req)
{
    if ((req->type() == QContactAbstractRequest::ContactSaveRequest
            && !static_cast<QContactSaveRequest*>(req)->definitionMask().isEmpty())
        || (req->type() == QContactAbstractRequest::ContactFetchByIdRequest)) {
        RequestController* controller;
        if (req->type() == QContactAbstractRequest::ContactFetchByIdRequest)
            controller = new FetchByIdRequestController(m_engine);
        else
            controller = new PartialSaveRequestController(m_engine, this);
        controller->setRequest(req);
        connect(controller, SIGNAL(stateChanged(QContactAbstractRequest::State)),
                this, SLOT(requestStateChanged(QContactAbstractRequest::State)),
                Qt::QueuedConnection);
        m_controllerForRequest.insert(req, controller);
        if (controller->start()) {
            updateRequestState(req, QContactAbstractRequest::ActiveState);
            return true;
        } else {
            return false;
        }
    }


    return m_engine->startRequest(req);
}
