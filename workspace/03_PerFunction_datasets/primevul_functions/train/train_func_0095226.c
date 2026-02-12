bool ContentSettingsObserver::IsPluginTemporarilyAllowed(
    const std::string& identifier) {


  return (temporarily_allowed_plugins_.find(identifier) !=
          temporarily_allowed_plugins_.end()) ||
         (temporarily_allowed_plugins_.find(std::string()) !=
          temporarily_allowed_plugins_.end());
}
