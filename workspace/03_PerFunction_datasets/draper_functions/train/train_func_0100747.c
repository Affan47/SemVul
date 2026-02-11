writeParamAllocateCode(Output& out, const TypePtr& type, const string& fixedName, const StringList& metaData,
                       int typeCtx)
{
    out << nl << typeToString(type, metaData, typeCtx) << ' ' << fixedName;
    StructPtr st = StructPtr::dynamicCast(type);
    if(st && findMetaData(st->getMetaData()) == "class")
    {
        out << " = new " << fixKwd(st->scoped());
    }
    out << ';';

    if(!(typeCtx & TypeContextInParam))
    {
        return;
    }


    SequencePtr seq = SequencePtr::dynamicCast(type);
    if(seq)
    {
        bool protobuf;
        string seqType = findMetaData(seq, metaData, protobuf, typeCtx);
        if(!protobuf && seqType.empty())
        {
            seqType = findMetaData(seq, seq->getMetaData(), protobuf, typeCtx);
        }
        if(protobuf)
        {
            return;
        }
        if(seqType == "array" || seqType == "range:array")
        {
            if(typeCtx & TypeContextAMICallPrivateEnd)
            {
                out << nl << typeToString(seq, metaData, TypeContextAMIPrivateEnd) << " ___" << fixedName << ";";


            }
        }
        else if(seqType.find("range") == 0)
        {
            StringList md;
            if(seqType.find("range:") == 0)
            {
                md.push_back("cpp:type:" + seqType.substr(strlen("range:")));
            }
            out << nl << typeToString(seq, md) << " ___" << fixedName << ";";
        }
    }
}
