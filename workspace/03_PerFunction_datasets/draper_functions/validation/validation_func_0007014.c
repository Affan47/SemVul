PrintInstruments(DLS::File* dls) {
    int instruments = 0;
    cout << "Available Instruments:" << endl;
    DLS::Instrument* pInstrument = dls->GetFirstInstrument();
    while (pInstrument) {
        instruments++;
        string name = pInstrument->pInfo->Name;
        if (name == "") name = "<NO NAME>";
        else            name = '\"' + name + '\"';
        cout << "    Instrument " << instruments << ") " << name << ", ";

        cout << " MIDIBank=" << pInstrument->MIDIBank << ", MIDIProgram=" << pInstrument->MIDIProgram << endl;
        PrintRegions(pInstrument);

        pInstrument = dls->GetNextInstrument();
    }
}
