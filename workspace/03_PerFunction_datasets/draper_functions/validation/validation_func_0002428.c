ensFeaturepairTrace(const EnsPFeaturepair fp, ajuint level)
{
    AjPStr indent = NULL;

    if (!fp)
        return ajFalse;

    indent = ajStrNew();

    ajStrAppendCountK(&indent, ' ', level * 2);

    ajDebug("ensFeaturepairTrace %p\n"
            "%S  SourceFeature %p\n"
            "%S  TargetFeature %p\n"
            "%S  Externaldatabase %p\n"
            "%S  Extradata %p\n"
            "%S  SourceSpecies '%S'\n"
            "%S  TargetSpecies '%S'\n"
            "%S  Groupidentifier %d\n"
            "%S  Levelidentifier %d\n"
            "%S  Use %u\n"
            "%S  Evalue %f\n"
            "%S  Score %f\n"
            "%S  SourceCoverage %f\n"
            "%S  TargetCoverage %f\n"
            "%S  Identity %f\n",
            indent, fp,
            indent, fp->SourceFeature,
            indent, fp->TargetFeature,
            indent, fp->Externaldatabase,
            indent, fp->Extradata,
            indent, fp->SourceSpecies,
            indent, fp->TargetSpecies,
            indent, fp->Groupidentifier,
            indent, fp->Levelidentifier,
            indent, fp->Use,
            indent, fp->Evalue,
            indent, fp->Score,
            indent, fp->SourceCoverage,
            indent, fp->TargetCoverage,
            indent, fp->Identity);

    ensFeatureTrace(fp->SourceFeature, level + 1);

    ensFeatureTrace(fp->TargetFeature, level + 1);

    ensExternaldatabaseTrace(fp->Externaldatabase, level + 1);

    ajStrDel(&indent);

    return ajTrue;
}
