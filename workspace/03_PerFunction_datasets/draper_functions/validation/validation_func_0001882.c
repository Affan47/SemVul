inf_communication_group_is_member(InfCommunicationGroup* group,
                                  InfXmlConnection* connection)
{
  InfCommunicationMethod* method;

  g_return_val_if_fail(INF_COMMUNICATION_IS_GROUP(group), FALSE);
  g_return_val_if_fail(INF_IS_XML_CONNECTION(connection), FALSE);

  method = inf_communication_group_lookup_method_for_connection(
    group,
    connection
  );

  if(method != NULL)
    return inf_communication_method_is_member(method, connection);
  else
    return FALSE;
}
