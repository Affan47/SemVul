cbProject_RenameBuildTarget(HSQUIRRELVM v)
    {
        StackHandler sa(v);
        int paramCount = sa.GetParamCount();
        if (paramCount == 3)
        {
            cbProject* prj = SqPlus::GetInstance<cbProject,false>(v, 1);
            if (sa.GetType(2) == OT_INTEGER)
                return sa.Return(prj->RenameBuildTarget(sa.GetInt(2), *SqPlus::GetInstance<wxString,false>(v, 3)));
            else
                return sa.Return(prj->RenameBuildTarget(*SqPlus::GetInstance<wxString,false>(v, 2), *SqPlus::GetInstance<wxString,false>(v, 3)));
        }
        return sa.ThrowError("Invalid arguments to \"cbProject::RenameBuildTarget\"");
    }
