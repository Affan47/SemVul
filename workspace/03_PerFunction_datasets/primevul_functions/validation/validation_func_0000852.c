int vt_ioctl(struct tty_struct *tty,
	     unsigned int cmd, unsigned long arg)
{
	struct vc_data *vc = tty->driver_data;
	struct console_font_op op;
	unsigned int console;
	unsigned char ucval;
	unsigned int uival;
	void __user *up = (void __user *)arg;
	int i, perm;
	int ret = 0;

	console = vc->vc_num;


	if (!vc_cons_allocated(console)) {
		ret = -ENOIOCTLCMD;
		goto out;
	}


	perm = 0;
	if (current->signal->tty == tty || capable(CAP_SYS_TTY_CONFIG))
		perm = 1;

	switch (cmd) {
	case TIOCLINUX:
		ret = tioclinux(tty, arg);
		break;
	case KIOCSOUND:
		if (!perm)
			return -EPERM;


		if (arg)
			arg = PIT_TICK_RATE / arg;
		kd_mksound(arg, 0);
		break;

	case KDMKTONE:
		if (!perm)
			return -EPERM;
	{
		unsigned int ticks, count;


		ticks = msecs_to_jiffies((arg >> 16) & 0xffff);
		count = ticks ? (arg & 0xffff) : 0;
		if (count)
			count = PIT_TICK_RATE / count;
		kd_mksound(count, ticks);
		break;
	}

	case KDGKBTYPE:


		ucval = KB_101;
		ret = put_user(ucval, (char __user *)arg);
		break;


#ifdef CONFIG_X86
	case KDADDIO:
	case KDDELIO:


		if (arg < GPFIRST || arg > GPLAST) {
			ret = -EINVAL;
			break;
		}
		ret = ksys_ioperm(arg, 1, (cmd == KDADDIO)) ? -ENXIO : 0;
		break;

	case KDENABIO:
	case KDDISABIO:
		ret = ksys_ioperm(GPFIRST, GPNUM,
				  (cmd == KDENABIO)) ? -ENXIO : 0;
		break;
#endif


	case KDKBDREP:
	{
		struct kbd_repeat kbrep;

		if (!capable(CAP_SYS_TTY_CONFIG))
			return -EPERM;

		if (copy_from_user(&kbrep, up, sizeof(struct kbd_repeat))) {
			ret =  -EFAULT;
			break;
		}
		ret = kbd_rate(&kbrep);
		if (ret)
			break;
		if (copy_to_user(up, &kbrep, sizeof(struct kbd_repeat)))
			ret = -EFAULT;
		break;
	}

	case KDSETMODE:


		if (!perm)
			return -EPERM;
		switch (arg) {
		case KD_GRAPHICS:
			break;
		case KD_TEXT0:
		case KD_TEXT1:
			arg = KD_TEXT;
		case KD_TEXT:
			break;
		default:
			ret = -EINVAL;
			goto out;
		}

		if (vc->vc_mode == (unsigned char) arg)
			break;
		vc->vc_mode = (unsigned char) arg;
		if (console != fg_console)
			break;


		console_lock();
		if (arg == KD_TEXT)
			do_unblank_screen(1);
		else
			do_blank_screen(1);
		console_unlock();
		break;

	case KDGETMODE:
		uival = vc->vc_mode;
		goto setint;

	case KDMAPDISP:
	case KDUNMAPDISP:


		ret = -EINVAL;
		break;

	case KDSKBMODE:
		if (!perm)
			return -EPERM;
		ret = vt_do_kdskbmode(console, arg);
		if (ret == 0)
			tty_ldisc_flush(tty);
		break;

	case KDGKBMODE:
		uival = vt_do_kdgkbmode(console);
		ret = put_user(uival, (int __user *)arg);
		break;


	case KDSKBMETA:
		ret = vt_do_kdskbmeta(console, arg);
		break;

	case KDGKBMETA:

		uival = vt_do_kdgkbmeta(console);
	setint:
		ret = put_user(uival, (int __user *)arg);
		break;

	case KDGETKEYCODE:
	case KDSETKEYCODE:
		if(!capable(CAP_SYS_TTY_CONFIG))
			perm = 0;
		ret = vt_do_kbkeycode_ioctl(cmd, up, perm);
		break;

	case KDGKBENT:
	case KDSKBENT:
		ret = vt_do_kdsk_ioctl(cmd, up, perm, console);
		break;

	case KDGKBSENT:
	case KDSKBSENT:
		ret = vt_do_kdgkb_ioctl(cmd, up, perm);
		break;


	case KDGKBDIACR:
	case KDGKBDIACRUC:
	case KDSKBDIACR:
	case KDSKBDIACRUC:
		ret = vt_do_diacrit(cmd, up, perm);
		break;


	case KDGKBLED:
	case KDSKBLED:
	case KDGETLED:
	case KDSETLED:
		ret = vt_do_kdskled(console, cmd, arg, perm);
		break;


	case KDSIGACCEPT:
	{
		if (!perm || !capable(CAP_KILL))
			return -EPERM;
		if (!valid_signal(arg) || arg < 1 || arg == SIGKILL)
			ret = -EINVAL;
		else {
			spin_lock_irq(&vt_spawn_con.lock);
			put_pid(vt_spawn_con.pid);
			vt_spawn_con.pid = get_pid(task_pid(current));
			vt_spawn_con.sig = arg;
			spin_unlock_irq(&vt_spawn_con.lock);
		}
		break;
	}

	case VT_SETMODE:
	{
		struct vt_mode tmp;

		if (!perm)
			return -EPERM;
		if (copy_from_user(&tmp, up, sizeof(struct vt_mode))) {
			ret = -EFAULT;
			goto out;
		}
		if (tmp.mode != VT_AUTO && tmp.mode != VT_PROCESS) {
			ret = -EINVAL;
			goto out;
		}
		console_lock();
		vc->vt_mode = tmp;

		vc->vt_mode.frsig = 0;
		put_pid(vc->vt_pid);
		vc->vt_pid = get_pid(task_pid(current));

		vc->vt_newvt = -1;
		console_unlock();
		break;
	}

	case VT_GETMODE:
	{
		struct vt_mode tmp;
		int rc;

		console_lock();
		memcpy(&tmp, &vc->vt_mode, sizeof(struct vt_mode));
		console_unlock();

		rc = copy_to_user(up, &tmp, sizeof(struct vt_mode));
		if (rc)
			ret = -EFAULT;
		break;
	}


	case VT_GETSTATE:
	{
		struct vt_stat __user *vtstat = up;
		unsigned short state, mask;


		if (put_user(fg_console + 1, &vtstat->v_active))
			ret = -EFAULT;
		else {
			state = 1;
			for (i = 0, mask = 2; i < MAX_NR_CONSOLES && mask;
							++i, mask <<= 1)
				if (VT_IS_IN_USE(i))
					state |= mask;
			ret = put_user(state, &vtstat->v_state);
		}
		break;
	}


	case VT_OPENQRY:

		for (i = 0; i < MAX_NR_CONSOLES; ++i)
			if (! VT_IS_IN_USE(i))
				break;
		uival = i < MAX_NR_CONSOLES ? (i+1) : -1;
		goto setint;


	case VT_ACTIVATE:
		if (!perm)
			return -EPERM;
		if (arg == 0 || arg > MAX_NR_CONSOLES)
			ret =  -ENXIO;
		else {
			arg--;
			console_lock();
			ret = vc_allocate(arg);
			console_unlock();
			if (ret)
				break;
			set_console(arg);
		}
		break;

	case VT_SETACTIVATE:
	{
		struct vt_setactivate vsa;

		if (!perm)
			return -EPERM;

		if (copy_from_user(&vsa, (struct vt_setactivate __user *)arg,
					sizeof(struct vt_setactivate))) {
			ret = -EFAULT;
			goto out;
		}
		if (vsa.console == 0 || vsa.console > MAX_NR_CONSOLES)
			ret = -ENXIO;
		else {
			vsa.console = array_index_nospec(vsa.console,
							 MAX_NR_CONSOLES + 1);
			vsa.console--;
			console_lock();
			ret = vc_allocate(vsa.console);
			if (ret == 0) {
				struct vc_data *nvc;


				nvc = vc_cons[vsa.console].d;
				nvc->vt_mode = vsa.mode;
				nvc->vt_mode.frsig = 0;
				put_pid(nvc->vt_pid);
				nvc->vt_pid = get_pid(task_pid(current));
			}
			console_unlock();
			if (ret)
				break;


			set_console(vsa.console);
		}
		break;
	}


	case VT_WAITACTIVE:
		if (!perm)
			return -EPERM;
		if (arg == 0 || arg > MAX_NR_CONSOLES)
			ret = -ENXIO;
		else
			ret = vt_waitactive(arg);
		break;


	case VT_RELDISP:
		if (!perm)
			return -EPERM;

		console_lock();
		if (vc->vt_mode.mode != VT_PROCESS) {
			console_unlock();
			ret = -EINVAL;
			break;
		}


		if (vc->vt_newvt >= 0) {
			if (arg == 0)


				vc->vt_newvt = -1;

			else {


				int newvt;
				newvt = vc->vt_newvt;
				vc->vt_newvt = -1;
				ret = vc_allocate(newvt);
				if (ret) {
					console_unlock();
					break;
				}


				complete_change_console(vc_cons[newvt].d);
			}
		} else {


			if (arg != VT_ACKACQ)
				ret = -EINVAL;
		}
		console_unlock();
		break;


	 case VT_DISALLOCATE:
		if (arg > MAX_NR_CONSOLES) {
			ret = -ENXIO;
			break;
		}
		if (arg == 0)
			vt_disallocate_all();
		else
			ret = vt_disallocate(--arg);
		break;

	case VT_RESIZE:
	{
		struct vt_sizes __user *vtsizes = up;
		struct vc_data *vc;

		ushort ll,cc;
		if (!perm)
			return -EPERM;
		if (get_user(ll, &vtsizes->v_rows) ||
		    get_user(cc, &vtsizes->v_cols))
			ret = -EFAULT;
		else {
			console_lock();
			for (i = 0; i < MAX_NR_CONSOLES; i++) {
				vc = vc_cons[i].d;

				if (vc) {
					vc->vc_resize_user = 1;

					vc_resize(vc_cons[i].d, cc, ll);
				}
			}
			console_unlock();
		}
		break;
	}

	case VT_RESIZEX:
	{
		struct vt_consize v;
		if (!perm)
			return -EPERM;
		if (copy_from_user(&v, up, sizeof(struct vt_consize)))
			return -EFAULT;

		if (!v.v_vlin)
			v.v_vlin = vc->vc_scan_lines;
		if (v.v_clin) {
			int rows = v.v_vlin/v.v_clin;
			if (v.v_rows != rows) {
				if (v.v_rows)
					return -EINVAL;
				v.v_rows = rows;
			}
		}
		if (v.v_vcol && v.v_ccol) {
			int cols = v.v_vcol/v.v_ccol;
			if (v.v_cols != cols) {
				if (v.v_cols)
					return -EINVAL;
				v.v_cols = cols;
			}
		}

		if (v.v_clin > 32)
			return -EINVAL;

		for (i = 0; i < MAX_NR_CONSOLES; i++) {
			if (!vc_cons[i].d)
				continue;
			console_lock();
			if (v.v_vlin)
				vc_cons[i].d->vc_scan_lines = v.v_vlin;
			if (v.v_clin)
				vc_cons[i].d->vc_font.height = v.v_clin;
			vc_cons[i].d->vc_resize_user = 1;
			vc_resize(vc_cons[i].d, v.v_cols, v.v_rows);
			console_unlock();
		}
		break;
	}

	case PIO_FONT: {
		if (!perm)
			return -EPERM;
		op.op = KD_FONT_OP_SET;
		op.flags = KD_FONT_FLAG_OLD | KD_FONT_FLAG_DONT_RECALC;
		op.width = 8;
		op.height = 0;
		op.charcount = 256;
		op.data = up;
		ret = con_font_op(vc_cons[fg_console].d, &op);
		break;
	}

	case GIO_FONT: {
		op.op = KD_FONT_OP_GET;
		op.flags = KD_FONT_FLAG_OLD;
		op.width = 8;
		op.height = 32;
		op.charcount = 256;
		op.data = up;
		ret = con_font_op(vc_cons[fg_console].d, &op);
		break;
	}

	case PIO_CMAP:
                if (!perm)
			ret = -EPERM;
		else
	                ret = con_set_cmap(up);
		break;

	case GIO_CMAP:
                ret = con_get_cmap(up);
		break;

	case PIO_FONTX:
	case GIO_FONTX:
		ret = do_fontx_ioctl(cmd, up, perm, &op);
		break;

	case PIO_FONTRESET:
	{
		if (!perm)
			return -EPERM;

#ifdef BROKEN_GRAPHICS_PROGRAMS


		ret = -ENOSYS;
		break;
#else
		{
		op.op = KD_FONT_OP_SET_DEFAULT;
		op.data = NULL;
		ret = con_font_op(vc_cons[fg_console].d, &op);
		if (ret)
			break;
		console_lock();
		con_set_default_unimap(vc_cons[fg_console].d);
		console_unlock();
		break;
		}
#endif
	}

	case KDFONTOP: {
		if (copy_from_user(&op, up, sizeof(op))) {
			ret = -EFAULT;
			break;
		}
		if (!perm && op.op != KD_FONT_OP_GET)
			return -EPERM;
		ret = con_font_op(vc, &op);
		if (ret)
			break;
		if (copy_to_user(up, &op, sizeof(op)))
			ret = -EFAULT;
		break;
	}

	case PIO_SCRNMAP:
		if (!perm)
			ret = -EPERM;
		else
			ret = con_set_trans_old(up);
		break;

	case GIO_SCRNMAP:
		ret = con_get_trans_old(up);
		break;

	case PIO_UNISCRNMAP:
		if (!perm)
			ret = -EPERM;
		else
			ret = con_set_trans_new(up);
		break;

	case GIO_UNISCRNMAP:
		ret = con_get_trans_new(up);
		break;

	case PIO_UNIMAPCLR:
		if (!perm)
			return -EPERM;
		con_clear_unimap(vc);
		break;

	case PIO_UNIMAP:
	case GIO_UNIMAP:
		ret = do_unimap_ioctl(cmd, up, perm, vc);
		break;

	case VT_LOCKSWITCH:
		if (!capable(CAP_SYS_TTY_CONFIG))
			return -EPERM;
		vt_dont_switch = 1;
		break;
	case VT_UNLOCKSWITCH:
		if (!capable(CAP_SYS_TTY_CONFIG))
			return -EPERM;
		vt_dont_switch = 0;
		break;
	case VT_GETHIFONTMASK:
		ret = put_user(vc->vc_hi_font_mask,
					(unsigned short __user *)arg);
		break;
	case VT_WAITEVENT:
		ret = vt_event_wait_ioctl((struct vt_event __user *)arg);
		break;
	default:
		ret = -ENOIOCTLCMD;
	}
out:
	return ret;
}
