afr_can_start_data_self_heal (afr_self_heal_t *sh, afr_private_t *priv)
{
        if (sh->force_confirm_spb)
                return _gf_true;
        if (sh->do_data_self_heal &&
            afr_data_self_heal_enabled (priv->data_self_heal))
                return _gf_true;
        return _gf_false;
}
