void CCrypto::Init()
{


    if(sodium_init() < 0)
    {
        AssertMsg( false, "libsodium didn't init" );
    }
}
