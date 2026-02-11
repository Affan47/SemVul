Java_magick_MagickImage_profileImage
  (JNIEnv *env, jobject self, jstring profileName, jbyteArray profileData)
{
    Image *image = NULL;
    const char *cstrProfileName;
    unsigned char *cProfileData;
    size_t cProfileSize;
    unsigned int retVal;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return JNI_FALSE;
    }

    if (profileName == NULL) {
        cstrProfileName = NULL;
    }
    else {
        cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
    }

    if (profileData == NULL) {
        cProfileData = NULL;
        cProfileSize = 0;
    }
    else {
        cProfileSize = (*env)->GetArrayLength(env, profileData);
        cProfileData = (*env)->GetByteArrayElements(env, profileData, 0);
    }


    retVal =
      ProfileImage(image, cstrProfileName, cProfileData, cProfileSize, 1);

    if (profileData != NULL) {
        (*env)->ReleaseByteArrayElements(env, profileData, cProfileData, 0);
    }

    if (profileName != NULL) {
        (*env)->ReleaseStringUTFChars(env, profileName, cstrProfileName);
    }

    return (retVal ? JNI_TRUE : JNI_FALSE);
}
