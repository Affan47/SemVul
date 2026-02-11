PrintFrameHelp(char *sName)
{
    for(int ii = 0; ii < frameTableCount - 1; ii++ )
    {
      std::cout << "    --" << frameTable[ii].frameName << "    "
           << frameTable[ii].frameLongName << std::endl;
    }
    return;
}
