void TiffEncoder::visitBinaryElement(TiffBinaryElement* object)
    {

        ByteOrder boOrig = byteOrder_;
        if (object->elByteOrder() != invalidByteOrder) byteOrder_ = object->elByteOrder();
        encodeTiffComponent(object);
        byteOrder_ = boOrig;
    }
