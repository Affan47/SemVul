VDir::VDir(int bManageDir )
{
    nDefault = 0;
    bManageDirectory = bManageDir;
    memset(dirTableA, 0, sizeof(dirTableA));
    memset(dirTableW, 0, sizeof(dirTableW));
}
