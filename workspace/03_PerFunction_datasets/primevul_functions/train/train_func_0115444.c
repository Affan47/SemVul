DataBuf PngChunk::keyTXTChunk(const DataBuf& data, bool stripHeader)
        {


            const size_t offset = stripHeader ? 8 : 0;
            if (data.size_ <= offset)
                throw Error(kerFailedToReadImageData);
            const byte* key = data.pData_ + offset;


            size_t keysize = 0;
            while (key[keysize] != 0) {
                keysize++;

                if (keysize + offset >= data.size_)
                    throw Error(kerFailedToReadImageData);
            }

            return DataBuf(key, keysize);

        }
