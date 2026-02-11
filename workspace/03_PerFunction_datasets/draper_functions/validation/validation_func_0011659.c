loadQualities(const std::string& filename)
{
    SeqReader reader(filename);
    SeqRecord sr;
    while(reader.get(sr))
        addQualityString(sr.qual);
}
