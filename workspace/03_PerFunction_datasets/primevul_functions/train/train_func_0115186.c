int XmpParser::decode(      XmpData&     xmpData,
                          const std::string& xmpPacket)
    { try {
        xmpData.clear();
        xmpData.setPacket(xmpPacket);
        if (xmpPacket.empty()) return 0;

        if (!initialize()) {
#ifndef SUPPRESS_WARNINGS
            EXV_ERROR << "XMP toolkit initialization failed.\n";
#endif
            return 2;
        }

        SXMPMeta meta(xmpPacket.data(), static_cast<XMP_StringLen>(xmpPacket.size()));
        SXMPIterator iter(meta);
        std::string schemaNs, propPath, propValue;
        XMP_OptionBits opt;
        while (iter.Next(&schemaNs, &propPath, &propValue, &opt)) {
            printNode(schemaNs, propPath, propValue, opt);
            if (XMP_PropIsAlias(opt)) {
                throw Error(kerAliasesNotSupported, schemaNs, propPath, propValue);
                continue;
            }
            if (XMP_NodeIsSchema(opt)) {


                if (XmpProperties::prefix(schemaNs).empty()) {
                    std::string prefix;
                    bool ret = meta.GetNamespacePrefix(schemaNs.c_str(), &prefix);
                    if (!ret) throw Error(kerSchemaNamespaceNotRegistered, schemaNs);
                    prefix = prefix.substr(0, prefix.size() - 1);
                    XmpProperties::registerNs(schemaNs, prefix);
                }
                continue;
            }
            XmpKey::UniquePtr key = makeXmpKey(schemaNs, propPath);
            if (XMP_ArrayIsAltText(opt)) {

                LangAltValue::UniquePtr val(new LangAltValue);
                XMP_Index count = meta.CountArrayItems(schemaNs.c_str(), propPath.c_str());
                while (count-- > 0) {

                    bool haveNext = iter.Next(&schemaNs, &propPath, &propValue, &opt);
                    printNode(schemaNs, propPath, propValue, opt);
                    if (   !haveNext
                        || !XMP_PropIsSimple(opt)
                        || !XMP_PropHasLang(opt)) {
                        throw Error(kerDecodeLangAltPropertyFailed, propPath, opt);
                    }
                    const std::string text = propValue;

                    haveNext = iter.Next(&schemaNs, &propPath, &propValue, &opt);
                    printNode(schemaNs, propPath, propValue, opt);
                    if (   !haveNext
                        || !XMP_PropIsSimple(opt)
                        || !XMP_PropIsQualifier(opt)
                        || propPath.substr(propPath.size() - 8, 8) != "xml:lang") {
                        throw Error(kerDecodeLangAltQualifierFailed, propPath, opt);
                    }
                    val->value_[propValue] = text;
                }
                xmpData.add(*key.get(), val.get());
                continue;
            }
            if (    XMP_PropIsArray(opt)
                && !XMP_PropHasQualifiers(opt)
                && !XMP_ArrayIsAltText(opt)) {

                bool simpleArray = true;
                SXMPIterator aIter(meta, schemaNs.c_str(), propPath.c_str());
                std::string aSchemaNs, aPropPath, aPropValue;
                XMP_OptionBits aOpt;
                while (aIter.Next(&aSchemaNs, &aPropPath, &aPropValue, &aOpt)) {
                    if (propPath == aPropPath) continue;
                    if (   !XMP_PropIsSimple(aOpt)
                        ||  XMP_PropHasQualifiers(aOpt)
                        ||  XMP_PropIsQualifier(aOpt)
                        ||  XMP_NodeIsSchema(aOpt)
                        ||  XMP_PropIsAlias(aOpt)) {
                        simpleArray = false;
                        break;
                    }
                }
                if (simpleArray) {

                    XmpArrayValue::UniquePtr val(new XmpArrayValue(arrayValueTypeId(opt)));
                    XMP_Index count = meta.CountArrayItems(schemaNs.c_str(), propPath.c_str());
                    while (count-- > 0) {
                        iter.Next(&schemaNs, &propPath, &propValue, &opt);
                        printNode(schemaNs, propPath, propValue, opt);
                        val->read(propValue);
                    }
                    xmpData.add(*key.get(), val.get());
                    continue;
                }
            }
            XmpTextValue::UniquePtr val(new XmpTextValue);
            if (   XMP_PropIsStruct(opt)
                || XMP_PropIsArray(opt)) {

                val->setXmpArrayType(xmpArrayType(opt));
                val->setXmpStruct(xmpStruct(opt));
                xmpData.add(*key.get(), val.get());
                continue;
            }
            if (   XMP_PropIsSimple(opt)
                || XMP_PropIsQualifier(opt)) {
                val->read(propValue);
                xmpData.add(*key.get(), val.get());
                continue;
            }

            throw Error(kerUnhandledXmpNode, key->key(), opt);
        }

        return 0;
    }
#ifndef SUPPRESS_WARNINGS
    catch (const XMP_Error& e) {
        EXV_ERROR << Error(kerXMPToolkitError, e.GetID(), e.GetErrMsg()) << "\n";
        xmpData.clear();
        return 3;
    }
#else
    catch (const XMP_Error&) {
        xmpData.clear();
        return 3;
    }
#endif
    }
