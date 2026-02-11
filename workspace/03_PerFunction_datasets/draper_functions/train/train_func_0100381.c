unload() {
    if(textureid!=0) glDeleteTextures(1, &textureid);
    textureid=0;
}
