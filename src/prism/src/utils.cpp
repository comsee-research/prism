#include "utils.h"

// Boost
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <pleno/io/printer.h>


Config_t parse_args(int argc, char *argv[])
{
	namespace po = boost::program_options;

	po::options_description desc("Options");
	
	desc.add_options()
		("help,h", "Print help messages")
		("gui,g", 
			po::value<bool>()->default_value(true),
			"Enable GUI (image viewers, etc.)"
		)
		("verbose,v", 
			po::value<bool>()->default_value(true),
			"Enable output with extra information"
		)
		("level,l", 
			po::value<std::uint16_t>()->default_value(Printer::Level::ALL),
			"Select level of output to print (can be combined):\n"
			"NONE=0, ERR=1, WARN=2, INFO=4, DEBUG=8, ALL=15"
		)
		("pcamera,c",
			po::value<std::string>()->default_value(""),
			"Path to camera configuration file"
		)
		("pparams,p",
			po::value<std::string>()->default_value(""),
			"Path to camera internal parameters configuration file"
		)
		("pscene,s",
			po::value<std::string>()->default_value(""),
			"Path to scene configuration file"
		)
		("nrays,n", 
			po::value<std::size_t>()->default_value(30),
			"Number of rays per pixel"
		)
		("vignetting", 
			po::value<bool>()->default_value(true),
			"Enable vignetting effect in modelization"
		)
		("save_all", 
			po::value<bool>()->default_value(false),
			"Save automaticaly all image"
		)
		("run_all", 
			po::value<bool>()->default_value(false),
			"Run automaticaly all image generation"
		);

	po::variables_map vm;
	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (po::error &e) {
		/* Invalid options */
		std::cerr << "Error: " << e.what() << std::endl << std::endl;
		std::cout << "PRISM: Plenoptic Raw Image Simulator:" << std::endl
		  << desc << std::endl;
		exit(0);
	}
	po::notify(vm);
	
	//check if hepl or no arguments then display usage
	if (vm.count("help") or argc==1)
	{
		/* print usage */
		std::cout << "PRISM: Plenoptic Raw Image Simulator:" << std::endl
				      << desc << std::endl;
		exit(0);
	}
	
	//check mandatory parameters
	if ( vm["pcamera"].as<std::string>() == "" or vm["pscene"].as<std::string>() == "")
	{
		/* print usage */
		std::cerr << "Please specify at the configuration files. " << std::endl;
		std::cout << "PRISM: Plenoptic Raw Image Simulator:" << std::endl
				      << desc << std::endl;
		exit(0);
	}
	
	
	Config_t config;
	
	config.use_gui 	 		= vm["gui"].as<bool>();
	config.verbose			= vm["verbose"].as<bool>();
	config.level			= vm["level"].as<std::uint16_t>();
	config.nrays			= vm["nrays"].as<std::size_t>();
	config.vignetting		= vm["vignetting"].as<bool>();
	config.path.camera 		= vm["pcamera"].as<std::string>();
	config.path.params 		= vm["pparams"].as<std::string>();
	config.path.scene 		= vm["pscene"].as<std::string>();
	
	config.save_all			= vm["save_all"].as<bool>();
	config.run_all			= vm["run_all"].as<bool>();
	
	return config; 
}

