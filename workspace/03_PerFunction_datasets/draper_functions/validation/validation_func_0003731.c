qrstat_report_start(qrstat_report_handler_t* handler, lList **alpp)
{
   bool ret = true;
   dstring *buffer = (dstring*)handler->ctx;

   DENTER(TOP_LAYER, "qrstat_report_start");

   sge_dstring_append(buffer, "<?xml version='1.0'?>\n");
   sge_dstring_append(buffer, "<qrstat xmlns:xsd=\"http://gridengine.sunsource.net/source/browse/*checkout*/gridengine/source/dist/util/resources/schemas/qrstat/qrstat.xsd?revision=1.2\">\n");

   DRETURN(ret);
}
