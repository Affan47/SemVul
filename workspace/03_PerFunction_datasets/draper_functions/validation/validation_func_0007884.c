mx_actor_manager_create_actor (MxActorManager           *manager,
                               MxActorManagerCreateFunc  create_func,
                               gpointer                  userdata,
                               GDestroyNotify            destroy_func)
{
  MxActorManagerOperation *op;

  g_return_val_if_fail (MX_IS_ACTOR_MANAGER (manager), 0);
  g_return_val_if_fail (create_func != NULL, 0);

  op = mx_actor_manager_op_new (manager,
                                MX_ACTOR_MANAGER_CREATE,
                                create_func,
                                userdata,
                                NULL,
                                NULL);

  mx_actor_manager_ensure_processing (manager);

  return op->id;
}
