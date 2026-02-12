AP4_Processor::Process(AP4_ByteStream&   input,
                       AP4_ByteStream&   output,
                       AP4_ByteStream*   fragments,
                       ProgressListener* listener,
                       AP4_AtomFactory&  atom_factory)
{


    AP4_AtomParent              top_level;
    AP4_MoovAtom*               moov = NULL;
    AP4_ContainerAtom*          mfra = NULL;
    AP4_SidxAtom*               sidx = NULL;
    AP4_List<AP4_AtomLocator>   frags;
    AP4_UI64                    stream_offset = 0;
    bool                        in_fragments = false;
    unsigned int                sidx_count = 0;
    for (AP4_Atom* atom = NULL;
        AP4_SUCCEEDED(atom_factory.CreateAtomFromStream(input, atom));
        input.Tell(stream_offset)) {
        if (atom->GetType() == AP4_ATOM_TYPE_MDAT) {
            delete atom;
            continue;
        } else if (atom->GetType() == AP4_ATOM_TYPE_MOOV) {
            moov = AP4_DYNAMIC_CAST(AP4_MoovAtom, atom);
            if (fragments) break;
        } else if (atom->GetType() == AP4_ATOM_TYPE_MFRA) {
            mfra = AP4_DYNAMIC_CAST(AP4_ContainerAtom, atom);
            continue;
        } else if (atom->GetType() == AP4_ATOM_TYPE_SIDX) {

            ++sidx_count;
            if (sidx == NULL) {
                sidx = AP4_DYNAMIC_CAST(AP4_SidxAtom, atom);
            } else {
                delete atom;
                continue;
            }
        } else if (atom->GetType() == AP4_ATOM_TYPE_SSIX) {

            delete atom;
            continue;
        } else if (!fragments && (in_fragments || atom->GetType() == AP4_ATOM_TYPE_MOOF)) {
            in_fragments = true;
            frags.Add(new AP4_AtomLocator(atom, stream_offset));
            continue;
        }
        top_level.AddChild(atom);
    }


    if (sidx_count > 1) {
        top_level.RemoveChild(sidx);
        delete sidx;
        sidx = NULL;
    }


    if (fragments) {
        stream_offset = 0;
        for (AP4_Atom* atom = NULL;
            AP4_SUCCEEDED(atom_factory.CreateAtomFromStream(*fragments, atom));
            fragments->Tell(stream_offset)) {
            if (atom->GetType() == AP4_ATOM_TYPE_MDAT) {
                delete atom;
                continue;
            }
            frags.Add(new AP4_AtomLocator(atom, stream_offset));
        }
    }


    AP4_Result result = Initialize(top_level, input);
    if (AP4_FAILED(result)) return result;


    AP4_Array<AP4_SampleLocator> locators;
    AP4_Cardinal                 track_count       = 0;
    AP4_List<AP4_TrakAtom>*      trak_atoms        = NULL;
    AP4_LargeSize                mdat_payload_size = 0;
    AP4_SampleCursor*            cursors           = NULL;
    if (moov) {

        trak_atoms = &moov->GetTrakAtoms();
        track_count = trak_atoms->ItemCount();
        cursors = new AP4_SampleCursor[track_count];
        m_TrackHandlers.SetItemCount(track_count);
        m_TrackIds.SetItemCount(track_count);
        for (AP4_Ordinal i=0; i<track_count; i++) {
            m_TrackHandlers[i] = NULL;
            m_TrackIds[i] = 0;
        }

        unsigned int index = 0;
        for (AP4_List<AP4_TrakAtom>::Item* item = trak_atoms->FirstItem(); item; item=item->GetNext()) {
            AP4_TrakAtom* trak = item->GetData();


            AP4_ContainerAtom* stbl = AP4_DYNAMIC_CAST(AP4_ContainerAtom, trak->FindChild("mdia/minf/stbl"));
            if (stbl == NULL) continue;


            AP4_ByteStream* trak_data_stream = &input;
            for (AP4_List<ExternalTrackData>::Item* ditem = m_ExternalTrackData.FirstItem(); ditem; ditem=ditem->GetNext()) {
                ExternalTrackData* tdata = ditem->GetData();
                if (tdata->m_TrackId == trak->GetId()) {
                    trak_data_stream = tdata->m_MediaData;
                    break;
                }
            }


            m_TrackHandlers[index] = CreateTrackHandler(trak);
            m_TrackIds[index]      = trak->GetId();
            cursors[index].m_Locator.m_TrakIndex   = index;
            cursors[index].m_Locator.m_SampleTable = new AP4_AtomSampleTable(stbl, *trak_data_stream);
            cursors[index].m_Locator.m_SampleIndex = 0;
            cursors[index].m_Locator.m_ChunkIndex  = 0;
            if (cursors[index].m_Locator.m_SampleTable->GetSampleCount()) {
                cursors[index].m_Locator.m_SampleTable->GetSample(0, cursors[index].m_Locator.m_Sample);
            } else {
                cursors[index].m_EndReached = true;
            }

            index++;
        }


        for (;;) {

            AP4_UI64 min_offset = (AP4_UI64)(-1);
            int cursor = -1;
            for (unsigned int i=0; i<track_count; i++) {
                if (!cursors[i].m_EndReached &&
                    cursors[i].m_Locator.m_Sample.GetOffset() <= min_offset) {
                    min_offset = cursors[i].m_Locator.m_Sample.GetOffset();
                    cursor = i;
                }
            }


            if (cursor == -1) break;


            AP4_SampleLocator& locator = cursors[cursor].m_Locator;
            locators.Append(locator);


            locator.m_SampleIndex++;
            if (locator.m_SampleIndex == locator.m_SampleTable->GetSampleCount()) {

                cursors[cursor].m_EndReached = true;
            } else {

                locator.m_SampleTable->GetSample(locator.m_SampleIndex, locator.m_Sample);
                AP4_Ordinal skip, sdesc;
                locator.m_SampleTable->GetChunkForSample(locator.m_SampleIndex,
                                                         locator.m_ChunkIndex,
                                                         skip, sdesc);
            }
        }


        int current_track = -1;
        int current_chunk = -1;
        AP4_Position current_chunk_offset = 0;
        AP4_Size current_chunk_size = 0;
        for (AP4_Ordinal i=0; i<locators.ItemCount(); i++) {
            AP4_SampleLocator& locator = locators[i];
            if ((int)locator.m_TrakIndex  != current_track ||
                (int)locator.m_ChunkIndex != current_chunk) {

                current_chunk_offset += current_chunk_size;
                current_chunk_size = 0;
                current_track = locator.m_TrakIndex;
                current_chunk = locator.m_ChunkIndex;
                locator.m_SampleTable->SetChunkOffset(locator.m_ChunkIndex, current_chunk_offset);
            }
            AP4_Size sample_size;
            TrackHandler* handler = m_TrackHandlers[locator.m_TrakIndex];
            if (handler) {
                sample_size = handler->GetProcessedSampleSize(locator.m_Sample);
                locator.m_SampleTable->SetSampleSize(locator.m_SampleIndex, sample_size);
            } else {
                sample_size = locator.m_Sample.GetSize();
            }
            current_chunk_size += sample_size;
            mdat_payload_size  += sample_size;
        }


        for (AP4_Ordinal i=0; i<track_count; i++) {
            TrackHandler* handler = m_TrackHandlers[i];
            if (handler) handler->ProcessTrack();
        }
    }


    Finalize(top_level);

    if (!fragments) {

        AP4_UI64 atoms_size = 0;
        top_level.GetChildren().Apply(AP4_AtomSizeAdder(atoms_size));


        AP4_Size mdat_header_size = AP4_ATOM_HEADER_SIZE;
        if (mdat_payload_size+mdat_header_size > 0xFFFFFFFF) {

            mdat_header_size += 8;
        }


        for (AP4_Ordinal i=0; i<track_count; i++) {
            AP4_TrakAtom* trak;
            trak_atoms->Get(i, trak);
            trak->AdjustChunkOffsets(atoms_size+mdat_header_size);
        }


        top_level.GetChildren().Apply(AP4_AtomListWriter(output));


        if (mdat_payload_size) {
            if (mdat_header_size == AP4_ATOM_HEADER_SIZE) {

                output.WriteUI32((AP4_UI32)(mdat_header_size+mdat_payload_size));
                output.WriteUI32(AP4_ATOM_TYPE_MDAT);
            } else {

                output.WriteUI32(1);
                output.WriteUI32(AP4_ATOM_TYPE_MDAT);
                output.WriteUI64(mdat_header_size+mdat_payload_size);
            }
        }
    }


    if (moov) {
        if (!fragments) {
#if defined(AP4_DEBUG)
            AP4_Position before;
            output.Tell(before);
#endif
            AP4_Sample     sample;
            AP4_DataBuffer data_in;
            AP4_DataBuffer data_out;
            for (unsigned int i=0; i<locators.ItemCount(); i++) {
                AP4_SampleLocator& locator = locators[i];
                locator.m_Sample.ReadData(data_in);
                TrackHandler* handler = m_TrackHandlers[locator.m_TrakIndex];
                if (handler) {
                    result = handler->ProcessSample(data_in, data_out);
                    if (AP4_FAILED(result)) return result;
                    output.Write(data_out.GetData(), data_out.GetDataSize());
                } else {
                    output.Write(data_in.GetData(), data_in.GetDataSize());
                }


                if (listener) {
                    listener->OnProgress(i+1, locators.ItemCount());
                }
            }

#if defined(AP4_DEBUG)
            AP4_Position after;
            output.Tell(after);
            AP4_ASSERT(after-before == mdat_payload_size);
#endif
        }


        AP4_Position sidx_position = 0;
        if (sidx) {
            for (AP4_List<AP4_Atom>::Item* item = top_level.GetChildren().FirstItem();
                                           item;
                                           item = item->GetNext()) {
                AP4_Atom* atom = item->GetData();
                if (atom->GetType() == AP4_ATOM_TYPE_SIDX) {
                    break;
                }
                sidx_position += atom->GetSize();
            }
        }


        result = ProcessFragments(moov, frags, mfra, sidx, sidx_position, fragments?*fragments:input, output);
        if (AP4_FAILED(result)) return result;


        if (sidx && sidx_position) {
            AP4_Position where = 0;
            output.Tell(where);
            output.Seek(sidx_position);
            result = sidx->Write(output);
            if (AP4_FAILED(result)) return result;
            output.Seek(where);
        }

        if (!fragments) {

            if (mfra) {
                mfra->Write(output);
            }
        }


        for (AP4_Ordinal i=0; i<track_count; i++) {
            delete cursors[i].m_Locator.m_SampleTable;
            delete m_TrackHandlers[i];
        }
        m_TrackHandlers.Clear();
        delete[] cursors;
    }


    frags.DeleteReferences();
    delete mfra;

    return AP4_SUCCESS;
}
