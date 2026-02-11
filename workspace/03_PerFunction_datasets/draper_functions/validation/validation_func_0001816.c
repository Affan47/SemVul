gnc_ttsplitinfo_set_credit_formula_numeric(TTSplitInfo *ttsi, gnc_numeric credit)
{
    g_return_if_fail(ttsi);

    if (ttsi->credit_formula)
        g_free(ttsi->credit_formula);

    ttsi->credit_formula = gnc_numeric_to_string(credit);

    if (ttsi->debit_formula)
    {
        g_free(ttsi->debit_formula);
        ttsi->debit_formula = NULL;
    }
}
