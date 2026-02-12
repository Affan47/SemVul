compressVerify (const unsigned short raw[],
                int n,
                const unsigned int dekHash)
{
    Array <char> compressed (3 * n + 4 * 65536);

    int nCompressed = hufCompress (raw, n, compressed);


    unsigned int compressedHash = nCompressed;
    const unsigned char* cptr = reinterpret_cast<const unsigned char*>( (const char*) compressed);
    for (int i = 0; i < nCompressed; ++i)
    {
        compressedHash =
            ((compressedHash << 5) ^ (compressedHash >> 27)) ^ (*cptr++);
    }

    cout << "verifying compressed checksum hash = "
        << compressedHash << std::endl;

    if (compressedHash != dekHash)
    {
       cout << "hash verification failed. Got " << compressedHash << " expected " << dekHash << std::endl;
       const unsigned char* cptr = reinterpret_cast<const unsigned char*>( (const char*) compressed);
       for(int i = 0 ; i < nCompressed ; ++i )
       {
           cout << std::hex << (0xFF & (int) (*cptr++));
           if ( (i & 0xF) ==0 )
           {
              cout << '\n';
           }
           else
           {
              cout << ' ';
           }
       }
       cout << "\n";
    }

    assert (compressedHash == dekHash);
}
