rest_proxy_call_invoke_async (RestProxyCall      *call,
                              GCancellable       *cancellable,
                              GAsyncReadyCallback callback,
                              gpointer            user_data)
{
  GSimpleAsyncResult *result;
  RestProxyCallPrivate *priv;
  SoupMessage *message;
  GError *error = NULL;

  g_return_if_fail (REST_IS_PROXY_CALL (call));
  priv = GET_PRIVATE (call);
  g_assert (priv->proxy);

  message = prepare_message (call, &error);
  if (message == NULL)
    {
      g_simple_async_report_take_gerror_in_idle (G_OBJECT (call), callback,
                                                 user_data, error);
      return;
    }

  result = g_simple_async_result_new (G_OBJECT (call), callback,
                                      user_data, rest_proxy_call_invoke_async);

  if (cancellable != NULL)
    g_signal_connect (cancellable, "cancelled",
        G_CALLBACK (_call_message_call_cancelled_cb), call);

  _rest_proxy_queue_message (priv->proxy,
                             message,
                             _call_message_call_completed_cb,
                             result);
}
