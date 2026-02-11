startExtension(const CompoundExtensionFlowObj &,
				const NodePtr &,
				Vector<FOTBuilder *> &ports)
{
  for (size_t i = 0; i < ports.size(); i++)
    ports[i] = this;
  start();
}
