init_mlme_ext_timer(struct adapter *padapter)
{
	struct	mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	setup_timer(&pmlmeext->survey_timer, survey_timer_hdl,
		    (unsigned long)padapter);
	setup_timer(&pmlmeext->link_timer, link_timer_hdl,
		    (unsigned long)padapter);
}
