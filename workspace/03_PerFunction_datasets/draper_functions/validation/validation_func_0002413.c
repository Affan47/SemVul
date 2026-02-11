print_metadata(poppler::document *doc)
{
    std::cout << std::setw(out_width) << "Metadata" << ":" << std::endl
              << doc->metadata() << std::endl;
    std::cout << std::endl;
}
