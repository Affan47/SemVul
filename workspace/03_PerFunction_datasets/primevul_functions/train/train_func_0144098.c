WriteMethod TiffParserWorker::encode(
              BasicIo&           io,
        const byte*              pData,
              uint32_t           size,
        const ExifData&          exifData,
        const IptcData&          iptcData,
        const XmpData&           xmpData,
              uint32_t           root,
              FindEncoderFct     findEncoderFct,
              TiffHeaderBase*    pHeader,
              OffsetWriter*      pOffsetWriter
    )
    {


        assert(pHeader);
        assert(pHeader->byteOrder() != invalidByteOrder);
        WriteMethod writeMethod = wmIntrusive;
        TiffComponent::AutoPtr parsedTree = parse(pData, size, root, pHeader);
        PrimaryGroups primaryGroups;
        findPrimaryGroups(primaryGroups, parsedTree.get());
        if (0 != parsedTree.get()) {

            TiffEncoder encoder(exifData,
                                iptcData,
                                xmpData,
                                parsedTree.get(),
                                false,
                                &primaryGroups,
                                pHeader,
                                findEncoderFct);
            parsedTree->accept(encoder);
            if (!encoder.dirty()) writeMethod = wmNonIntrusive;
        }
        if (writeMethod == wmIntrusive) {
            TiffComponent::AutoPtr createdTree = TiffCreator::create(root, ifdIdNotSet);
            if (0 != parsedTree.get()) {

                TiffCopier copier(createdTree.get(), root, pHeader, &primaryGroups);
                parsedTree->accept(copier);
            }

            TiffEncoder encoder(exifData,
                                iptcData,
                                xmpData,
                                createdTree.get(),
                                parsedTree.get() == 0,
                                &primaryGroups,
                                pHeader,
                                findEncoderFct);
            encoder.add(createdTree.get(), parsedTree.get(), root);

            DataBuf header = pHeader->write();
            BasicIo::AutoPtr tempIo(io.temporary());
            assert(tempIo.get() != 0);
            IoWrapper ioWrapper(*tempIo, header.pData_, header.size_, pOffsetWriter);
            uint32_t imageIdx(uint32_t(-1));
            createdTree->write(ioWrapper,
                               pHeader->byteOrder(),
                               header.size_,
                               uint32_t(-1),
                               uint32_t(-1),
                               imageIdx);
            if (pOffsetWriter) pOffsetWriter->writeOffsets(*tempIo);
            io.transfer(*tempIo);
#ifndef SUPPRESS_WARNINGS
            EXV_INFO << "Write strategy: Intrusive\n";
#endif
        }
#ifndef SUPPRESS_WARNINGS
        else {
            EXV_INFO << "Write strategy: Non-intrusive\n";
        }
#endif
        return writeMethod;
    }
