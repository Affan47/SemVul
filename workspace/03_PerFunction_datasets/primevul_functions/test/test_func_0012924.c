static void reds_client_monitors_config(RedsState *reds, VDAgentMonitorsConfig *monitors_config)
{
    FOREACH_QXL_INSTANCE(reds, qxl) {
        if (!red_qxl_client_monitors_config(qxl, monitors_config)) {

            spice_debug("QXLInterface::client_monitors_config failed");
        }
    }
}
