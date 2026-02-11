ConverttoGvar(gvarpkg *gp, Object obj)
{
    gvar *gv;

    gv = _dxf_ExCreateGvar (gp->type);
    if(obj)
        _dxf_ExDefineGvar (gv, obj);
    gv->reccrc = gp->reccrc;
    gv->cost = gp->cost;
    gv->skip = (_skip_state) gp->skip;
    gv->disable_cache = gp->disable_cache;
    gv->procId = gp->procId;
    return(gv);
}
