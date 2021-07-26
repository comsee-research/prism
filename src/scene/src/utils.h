#pragma once

#include <iostream>
#include <string>

struct Config_t {
	bool use_gui;
	bool verbose;
	std::uint16_t level;
	
	std::size_t nposes;
	
	double min, max;
	
	struct {
		std::string camera;
		std::string params;
		std::string scene;
	} path;
};

Config_t parse_args(int argc, char *argv[]);
