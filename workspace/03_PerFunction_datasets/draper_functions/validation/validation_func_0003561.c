setWindowType(WindowType type) {
    if (p->role != Client) return;

    int len;
    long data[2];

    switch (type) {
    case Override:


	data[0] = kde_net_wm_window_type_override;
	data[1] = net_wm_window_type_normal;
	len = 2;
	break;

    case  Dialog:
	data[0] = net_wm_window_type_dialog;
	data[1] = None;
	len = 1;
	break;

    case Menu:
	data[0] = net_wm_window_type_menu;
	data[1] = None;
	len = 1;
	break;

    case TopMenu:


	data[0] = kde_net_wm_window_type_topmenu;
	data[1] = net_wm_window_type_dock;
	len = 2;
	break;

    case Toolbar:
	data[0] = net_wm_window_type_toolbar;
	data[1] = None;
	len = 1;
	break;

    case Dock:
	data[0] = net_wm_window_type_dock;
	data[1] = None;
	len = 1;
	break;

    case Desktop:
	data[0] = net_wm_window_type_desktop;
	data[1] = None;
	len = 1;
	break;

    case Utility:
	data[0] = net_wm_window_type_utility;
	data[1] = net_wm_window_type_dialog;
	len = 2;
	break;

    case Splash:
	data[0] = net_wm_window_type_splash;
	data[1] = net_wm_window_type_dock;
	len = 2;
	break;

    case DropdownMenu:
	data[0] = net_wm_window_type_dropdown_menu;
	data[1] = net_wm_window_type_menu;
	len = 1;
	break;

    case PopupMenu:
	data[0] = net_wm_window_type_popup_menu;
	data[1] = net_wm_window_type_menu;
	len = 1;
	break;

    case Tooltip:
	data[0] = net_wm_window_type_tooltip;
	data[1] = None;
	len = 1;
	break;

    case Notification:
	data[0] = net_wm_window_type_notification;
	data[1] = net_wm_window_type_utility;
	len = 1;
	break;

    case ComboBox:
	data[0] = net_wm_window_type_combobox;
	data[1] = None;
	len = 1;
	break;

    case DNDIcon:
	data[0] = net_wm_window_type_dnd;
	data[1] = None;
	len = 1;
	break;

    default:
    case Normal:
	data[0] = net_wm_window_type_normal;
	data[1] = None;
	len = 1;
	break;
    }

    XChangeProperty(p->display, p->window, net_wm_window_type, XA_ATOM, 32,
		    PropModeReplace, (unsigned char *) &data, len);
}
