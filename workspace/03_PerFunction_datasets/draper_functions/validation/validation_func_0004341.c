is_automatic_inference_enabled()
{
    CYG_REPORT_FUNCNAMETYPE("CdlTransaction::is_automatic_inference_enabled", "result %d");

    bool result = inference_enabled;

    CYG_REPORT_RETVAL(result);
    return result;
}
