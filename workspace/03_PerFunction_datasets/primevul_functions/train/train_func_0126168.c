UserInfoChars()
{


    static const auto userInfoValid = CharacterSet("userinfo", ":-._~%!$&'()*+,;=") +
                                      CharacterSet::ALPHA +
                                      CharacterSet::DIGIT;
    return userInfoValid;
}
