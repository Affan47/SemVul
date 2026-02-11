ladish_cqueue_cancel(struct ladish_cqueue * queue_ptr)
{
  struct list_head * node_ptr;
  struct ladish_command * cmd_ptr;

  if (list_empty(&queue_ptr->queue))
  {
    return;
  }

  node_ptr = queue_ptr->queue.next;
  cmd_ptr = list_entry(node_ptr, struct ladish_command, siblings);
  if (cmd_ptr->state != LADISH_COMMAND_STATE_WAITING)
  {
    ladish_cqueue_clear(queue_ptr);
    return;
  }


  while (queue_ptr->queue.next != queue_ptr->queue.prev)
  {
    node_ptr = queue_ptr->queue.prev;
    list_del(node_ptr);

    cmd_ptr = list_entry(node_ptr, struct ladish_command, siblings);

    if (cmd_ptr->destructor != NULL)
    {
      cmd_ptr->destructor(cmd_ptr->context);
    }

    free(cmd_ptr);
  }

  queue_ptr->cancel = true;
  cmd_ptr->cancel = true;
}
