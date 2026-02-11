xaccSplitScrub (Split *split)
{
    Account *account;
    Transaction *trans;
    gnc_numeric value, amount;
    gnc_commodity *currency, *acc_commodity;
    int scu;

    if (!split) return;
    ENTER ("(split=%p)", split);

    trans = xaccSplitGetParent (split);
    if (!trans)
    {
        LEAVE("no trans");
        return;
    }

    account = xaccSplitGetAccount (split);


    if (!account)
    {
        xaccTransScrubOrphans (trans);
        account = xaccSplitGetAccount (split);
    }


    if (!account)
    {
        PINFO ("Free Floating Transaction!");
        LEAVE ("no account");
        return;
    }


    value = xaccSplitGetValue (split);
    if (gnc_numeric_check (value))
    {
        value = gnc_numeric_zero();
        xaccSplitSetValue (split, value);
    }

    amount = xaccSplitGetAmount (split);
    if (gnc_numeric_check (amount))
    {
        amount = gnc_numeric_zero();
        xaccSplitSetAmount (split, amount);
    }

    currency = xaccTransGetCurrency (trans);


    acc_commodity = xaccAccountGetCommodity(account);
    if (!acc_commodity)
    {
        xaccAccountScrubCommodity (account);
    }
    if (!acc_commodity || !gnc_commodity_equiv(acc_commodity, currency))
    {
        LEAVE ("(split=%p) inequiv currency", split);
        return;
    }

    scu = MIN (xaccAccountGetCommoditySCU (account),
               gnc_commodity_get_fraction (currency));

    if (gnc_numeric_same (amount, value, scu, GNC_HOW_RND_ROUND_HALF_UP))
    {
        LEAVE("(split=%p) different values", split);
        return;
    }


    PINFO ("Adjusted split with mismatched values, desc=\"%s\" memo=\"%s\""
           " old amount %s %s, new amount %s",
           trans->description, split->memo,
           gnc_num_dbg_to_string (xaccSplitGetAmount(split)),
           gnc_commodity_get_mnemonic (currency),
           gnc_num_dbg_to_string (xaccSplitGetValue(split)));

    xaccTransBeginEdit (trans);
    xaccSplitSetAmount (split, value);
    xaccTransCommitEdit (trans);
    LEAVE ("(split=%p)", split);
}
