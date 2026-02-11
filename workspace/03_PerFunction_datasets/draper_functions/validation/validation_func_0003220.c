threadisdead (Thread *thread)
{
  Thread *next_sibling, *parent, *xthread;

  if (! is_thread_locked()) {
    DPRINTF("MTCP: Internal error: threadisdead called without thread lock\n");
    mtcp_abort ();
  }
  DPRINTF("thread %p -> tid %d\n", thread, thread -> tid);


  if (thread -> prev != NULL) {
    thread -> prev -> next = thread -> next;
  }
  if (thread -> next != NULL) {
    thread -> next -> prev = thread -> prev;
  }
  if (thread == threads) {
    threads = threads->next;
  }

  parent = thread -> parent;
  if (parent == NULL) {
    MTCP_PRINTF("MTCP Internal Error: Orphaned Child Thread found: %d\n",
                thread->tid);
    mtcp_abort();
  }

  if (parent->children == thread) {
    parent->children = thread->siblings;
  } else {
    for (xthread = parent->children;
         xthread->siblings != thread;
         xthread = xthread->siblings) {}
    xthread->siblings = thread -> siblings;
  }


  for (xthread = thread->children; xthread != NULL; xthread = next_sibling) {
    next_sibling = xthread->siblings;
    xthread->parent = parent;
    xthread->siblings = parent->children;
    parent->children = xthread;
  }


  mtcp_state_futex (&(thread -> state), FUTEX_WAKE, 1, NULL);
  mtcp_state_destroy( &(thread -> state) );
  mtcp_put_thread_on_freelist(thread);
}
