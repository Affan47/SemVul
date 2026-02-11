get_mcc_service(Arc::PluginArgument* arg) {
    Arc::MCCPluginArgument* mccarg =
            arg?dynamic_cast<Arc::MCCPluginArgument*>(arg):NULL;
    if(!mccarg) return NULL;
    return new ArcMCCMsgValidator::MCC_MsgValidator_Service((Arc::Config*)(*mccarg),mccarg);
}
