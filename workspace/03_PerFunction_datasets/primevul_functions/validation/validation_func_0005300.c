bool ForwardCompatibilityWindowPassed(const VersionDef& versions) {


  return (versions.producer() - TF_GRAPH_DEF_VERSION) > 21;
}
