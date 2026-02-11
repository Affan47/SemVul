profile1Input(string profile1Name)
{
    int code;

    alignmentObj.clearAlignment();
    userParameters->setProfileNum(1);

    userParameters->setSeqName(profile1Name);
    userParameters->setProfile1Name(profile1Name);

    FileReader readProfileFile;
    code = readProfileFile.profileInput(&alignmentObj);


    if(!userParameters->getInteractive())
    {


        if(code != OK)
        {
            if (code==NOSEQUENCESINFILE)
                cerr << "ERROR: There are no sequences in profile2 file." << std::endl;
            else if (code==ALLNAMESNOTDIFFERENT)
                cerr << "ERROR: Not all sequence names are different" << std::endl;
            else
                cerr << "ERROR: Unhandled error code (" << code << ") returned from profileInput.\n";

            exit(2);
        }
    }

    return code;
}
