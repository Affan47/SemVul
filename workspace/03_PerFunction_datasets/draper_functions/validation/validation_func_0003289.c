inf_communication_factory_instantiate(InfCommunicationFactory* factory,
                                      const gchar* network,
                                      const gchar* method_name,
                                      InfCommunicationRegistry* registry,
                                      InfCommunicationGroup* group)
{
  InfCommunicationFactoryIface* iface;

  g_return_val_if_fail(INF_COMMUNICATION_IS_FACTORY(factory), NULL);
  g_return_val_if_fail(network != NULL, NULL);
  g_return_val_if_fail(method_name != NULL, NULL);
  g_return_val_if_fail(INF_COMMUNICATION_IS_REGISTRY(registry), NULL);
  g_return_val_if_fail(INF_COMMUNICATION_IS_GROUP(group), NULL);

  iface = INF_COMMUNICATION_FACTORY_GET_IFACE(factory);
  g_return_val_if_fail(iface->instantiate != NULL, NULL);

  return iface->instantiate(factory, network, method_name, registry, group);
}
