HttpStateData::handleRequestBodyProducerAborted()
{
    Client::handleRequestBodyProducerAborted();
    if (entry->isEmpty()) {
        debugs(11, 3, "request body aborted: " << serverConnection);


        ErrorState *err = new ErrorState(ERR_ICAP_FAILURE, Http::scInternalServerError, fwd->request);
        err->detailError(ERR_DETAIL_SRV_REQMOD_REQ_BODY);
        fwd->fail(err);
    }

    abortTransaction("request body producer aborted");
}
