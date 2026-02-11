wxString_OpCmp(HSQUIRRELVM v)
    {
        StackHandler sa(v);
        wxString& str1 = *SqPlus::GetInstance<wxString,false>(v, 1);
        if (sa.GetType(2) == OT_STRING)
            return sa.Return((SQInteger)str1.Cmp(cbC2U(sa.GetString(2))));
        return sa.Return((SQInteger)str1.Cmp(*SqPlus::GetInstance<wxString,false>(v, 2)));
    }
