initialiseResourceGroupDirectories()
{
    using namespace Ogre;
    ResourceGroupManager& rgm = ResourceGroupManager::getSingleton();


    rgm.createResourceGroup("imagesets");
    rgm.createResourceGroup("fonts");
    rgm.createResourceGroup("layouts");
    rgm.createResourceGroup("schemes");
    rgm.createResourceGroup("looknfeels");
    rgm.createResourceGroup("lua_scripts");
    rgm.createResourceGroup("schemas");


    ResourceGroupManager::getSingleton().addResourceLocation("./", "FileSystem");

    const char* dataPathPrefix = getDataPathPrefix();
    char resourcePath[PATH_MAX];


    sprintf(resourcePath, "%s/%s", dataPathPrefix, "schemes/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "schemes");
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "imagesets/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "imagesets");
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "fonts/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "fonts");
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "layouts/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "layouts");
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "looknfeel/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "looknfeels");
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "lua_scripts/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "lua_scripts");
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "xml_schemas/");
    ResourceGroupManager::getSingleton().addResourceLocation(resourcePath, "FileSystem", "schemas");
}
