battery_status_descr (apm_info * apmi)
{
	return
		IS_ABSENT(*apmi) ?
			"absent" :
			IS_CHARGING(*apmi) ?
				"charging" :
				ISNT_ON_LINE(*apmi) ?
					"discharging" : "not charging";
}
