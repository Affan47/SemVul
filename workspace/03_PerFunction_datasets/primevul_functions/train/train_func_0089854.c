void vncProperties::ExpandBox(HWND hDlg, BOOL fExpand)
{


	if (fExpand == m_bExpanded) return;

	RECT rcWnd, rcDefaultBox, rcChild, rcIntersection;
	HWND wndChild = NULL;
	HWND wndDefaultBox = NULL;


	HWND  pCtrl = GetDlgItem(hDlg, IDC_SHOWOPTIONS);
	if (pCtrl == NULL) return;

	wndDefaultBox = GetDlgItem(hDlg, IDC_DEFAULTBOX);
	if (wndDefaultBox == NULL) return;

	if (!fExpand) SendMessage(GetDlgItem(hDlg, IDC_BUTTON_EXPAND), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmpExpand);
	else SendMessage(GetDlgItem(hDlg, IDC_BUTTON_EXPAND), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmpCollaps);

	GetWindowRect(wndDefaultBox, &rcDefaultBox);


	wndChild = GetTopWindow(hDlg);

	for (; wndChild != NULL; wndChild = GetWindow(wndChild, GW_HWNDNEXT))
	{

		GetWindowRect(wndChild, &rcChild);

		if (!IntersectRect(&rcIntersection, &rcChild, &rcDefaultBox))
		{
			EnableWindow(wndChild, fExpand);
		}
	}

	if (!fExpand)
	{
		_ASSERT(m_bExpanded);
		GetWindowRect(hDlg, &rcWnd);


		if (cx == 0 && cy == 0)
		{
			cx = rcDefaultBox.right - rcWnd.left;
			cy = rcWnd.bottom - rcWnd.top;


			ShowWindow(wndDefaultBox, SW_HIDE);
		}


		SetWindowPos(hDlg, NULL, 0, 0,
			rcDefaultBox.right - rcWnd.left,
			rcDefaultBox.bottom - rcWnd.top,
			SWP_NOZORDER | SWP_NOMOVE);

		SetWindowText(pCtrl, "Advanced options");


		m_bExpanded = FALSE;
	}
	else
	{
		_ASSERT(!m_bExpanded);
		SetWindowPos(hDlg, NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE);


		SendMessage(hDlg, DM_REPOSITION, 0, 0);
		SetWindowText(pCtrl, "Hide");
		m_bExpanded = TRUE;
	}
}
