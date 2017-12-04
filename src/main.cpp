int main (int argc, const char **argv)
{
	if(argc < 2) {
		exit(1);
	}

	std::cout << "Running benchmark with data in " << std::string(argv[1]) << std::endl;
}