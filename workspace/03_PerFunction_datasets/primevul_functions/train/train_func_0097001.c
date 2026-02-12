void AcceptRoutingHandler<Pipeline, R>::onError(
    uint64_t connId,
    folly::exception_wrapper ex) {
  VLOG(4) << "Exception while parsing routing data: " << ex.what();


  auto ctx = getContext();
  auto pipeline =
      CHECK_NOTNULL(dynamic_cast<AcceptPipeline*>(ctx->getPipeline()));
  pipeline->readException(ex);


  routingPipelines_.erase(connId);
}
