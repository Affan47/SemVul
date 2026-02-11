qib_unregister_observers(struct qib_devdata *dd)
{
	struct diag_observer_list_elt *olp;
	unsigned long flags;

	spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
	olp = dd->diag_observer_list;
	while (olp) {

		dd->diag_observer_list = olp->next;
		spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
		vfree(olp);

		spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
		olp = dd->diag_observer_list;
	}
	spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
}
