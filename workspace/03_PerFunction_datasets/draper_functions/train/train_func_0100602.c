qlcnic_83xx_idc_check_state_validity(struct qlcnic_adapter *adapter,
						u32 state)
{
	u32 cur, prev, next;

	cur = adapter->ahw->idc.curr_state;
	prev = adapter->ahw->idc.prev_state;
	next = state;

	if ((next < QLC_83XX_IDC_DEV_COLD) ||
	    (next > QLC_83XX_IDC_DEV_QUISCENT)) {
		dev_err(&adapter->pdev->dev,
			"%s: curr %d, prev %d, next state %d is  invalid\n",
			__func__, cur, prev, state);
		return 1;
	}

	if ((cur == QLC_83XX_IDC_DEV_UNKNOWN) &&
	    (prev == QLC_83XX_IDC_DEV_UNKNOWN)) {
		if ((next != QLC_83XX_IDC_DEV_COLD) &&
		    (next != QLC_83XX_IDC_DEV_READY)) {
			dev_err(&adapter->pdev->dev,
				"%s: failed, cur %d prev %d next %d\n",
				__func__, cur, prev, next);
			return 1;
		}
	}

	if (next == QLC_83XX_IDC_DEV_INIT) {
		if ((prev != QLC_83XX_IDC_DEV_INIT) &&
		    (prev != QLC_83XX_IDC_DEV_COLD) &&
		    (prev != QLC_83XX_IDC_DEV_NEED_RESET)) {
			dev_err(&adapter->pdev->dev,
				"%s: failed, cur %d prev %d next %d\n",
				__func__, cur, prev, next);
			return 1;
		}
	}

	return 0;
}
