void tty_open_proc_set_tty(struct file *filp, struct tty_struct *tty)
{
	read_lock(&tasklist_lock);
	spin_lock_irq(&current->sighand->siglock);
	if (current->signal->leader &&
	    !current->signal->tty &&
	    tty->session == NULL) {


		if (filp->f_mode & FMODE_READ)
			__proc_set_tty(tty);
	}
	spin_unlock_irq(&current->sighand->siglock);
	read_unlock(&tasklist_lock);
}
