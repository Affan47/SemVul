PLT_HttpServer::ServeStream(const NPT_HttpRequest&        request,
                            const NPT_HttpRequestContext& context,
                            NPT_HttpResponse&             response,
                            NPT_InputStreamReference&     body,
                            const char*                   content_type)
{
    if (body.IsNull()) return NPT_FAILURE;


    NPT_TimeStamp now;
    NPT_System::GetCurrentTimeStamp(now);
    response.GetHeaders().SetHeader("Date", NPT_DateTime(now).ToString(NPT_DateTime::FORMAT_RFC_1123), true);


    NPT_HttpEntity* entity = response.GetEntity();
    NPT_CHECK_POINTER_FATAL(entity);


    entity->SetContentType(content_type);


    const NPT_String* range_spec = request.GetHeaders().GetHeaderValue(NPT_HTTP_HEADER_RANGE);


    NPT_CHECK(NPT_HttpFileRequestHandler::SetupResponseBody(response, body, range_spec));


    if (response.GetEntity()->GetTransferEncoding() != NPT_HTTP_TRANSFER_ENCODING_CHUNKED) {

        NPT_Position offset;
        if (NPT_SUCCEEDED(body->Tell(offset)) && NPT_SUCCEEDED(body->Seek(offset))) {
            response.GetHeaders().SetHeader(NPT_HTTP_HEADER_ACCEPT_RANGES, "bytes", false);
        }
    }


    const NPT_String* value = request.GetHeaders().GetHeaderValue("getcontentFeatures.dlna.org");
    if (value) {
        PLT_HttpRequestContext tmp_context(request, context);
        const char* dlna = PLT_ProtocolInfo::GetDlnaExtension(entity->GetContentType(),
                                                              &tmp_context);
        if (dlna) response.GetHeaders().SetHeader("ContentFeatures.DLNA.ORG", dlna, false);
    }


    value = request.GetHeaders().GetHeaderValue("transferMode.dlna.org");
    if (value) {


        response.GetHeaders().SetHeader("TransferMode.DLNA.ORG", value->GetChars(), false);
    } else {
        response.GetHeaders().SetHeader("TransferMode.DLNA.ORG", "Streaming", false);
    }

    if (request.GetHeaders().GetHeaderValue("TimeSeekRange.dlna.org")) {
        response.SetStatus(406, "Not Acceptable");
        return NPT_SUCCESS;
    }

    return NPT_SUCCESS;
}
