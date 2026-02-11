qif_parse_parse_account(gpointer key, gpointer val, gpointer data)
{
    parse_helper_t helper = data;
    QifAccount acct = val;

    QIF_PARSE_PARSE_NUMBER(acct->limitstr, helper->limit, &acct->limit);
    QIF_PARSE_PARSE_NUMBER(acct->budgetstr, helper->budget, &acct->budget);
}
