operator<<(ostream& out,TClntCfgPD& pd)
{
    out << "        <pd iaid=\"" << pd.IAID << "\" state=\"" << StateToString(pd.State) << "\" t1=\""
	<< pd.T1 << "\" t2=\"" << pd.T2 << "\" prefixes=\"" << pd.ClntCfgPrefixLst.count() << "\">" << std::endl;

    SPtr<TClntCfgPrefix> prefix;

    pd.ClntCfgPrefixLst.first();
    while(prefix=pd.ClntCfgPrefixLst.get())
    {
        out << "          " << *prefix;
    }
    out << "        </pd>" << std::endl;
    return out;
}
