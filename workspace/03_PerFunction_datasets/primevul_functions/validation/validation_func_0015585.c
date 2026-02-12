ConnStateData::checkLogging()
{

    if (bodyPipe)
        return;


    if (!pipeline.empty() && pipeline.back()->mayUseConnection())
        return;


    if (pipeline.nrequests && inBuf.isEmpty())
        return;


    ClientHttpRequest http(this);
    http.req_sz = inBuf.length();

    http.setErrorUri("error:transaction-end-before-headers");
}
