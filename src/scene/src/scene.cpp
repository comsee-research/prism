//STD
#include <iostream>
#include <unistd.h>
#include <chrono>
//EIGEN
//BOOST
//OPENCV
#include <opencv2/opencv.hpp>

//LIBPLENO
#include <pleno/types.h>

#include <pleno/graphic/gui.h>
#include <pleno/graphic/viewer_2d.h>
#include <pleno/graphic/display.h>

#include <pleno/io/printer.h>
#include <pleno/io/choice.h>

//geometry
#include <pleno/geometry/camera/plenoptic.h>
//simulation
#include <pleno/simulation/generate/generate.h> 

//config
#include <pleno/io/cfg/images.h>
#include <pleno/io/cfg/camera.h>
#include <pleno/io/cfg/scene.h>
#include <pleno/io/cfg/poses.h>

#include "utils.h"

int main(int argc, char* argv[])
{
	PRINT_INFO("========= PRISM: Plenoptic Raw Image Simulator (Scene generation) =========");
	Config_t config = parse_args(argc, argv);
	
	Viewer::enable(true);
	
	Printer::verbose(config.verbose);
	Printer::level(config.level);
	
////////////////////////////////////////////////////////////////////////////////	
	PRINT_WARN("Loading Camera information from configuration file...");
	PlenopticCamera mfpc;
	load(config.path.camera, mfpc);
	DEBUG_VAR(mfpc);
	
////////////////////////////////////////////////////////////////////////////////	
	InternalParameters params;
	if (config.path.params != "")
	{
		v::load(config.path.params, v::make_serializable(&params));
		mfpc.params() = params;
	}
////////////////////////////////////////////////////////////////////////////////	
	PRINT_WARN("Loading Scene Models...");
	SceneConfig cfg_scene;
	v::load(config.path.scene, cfg_scene);
	
	DEBUG_ASSERT((cfg_scene.checkerboards().size() == 1), "You need to provide checkerboard information");
	DEBUG_ASSERT((cfg_scene.plates().size() == 1), "You need to provide texture and dimension information for plate");

	CheckerBoard cb = cfg_scene.checkerboards()[0];
	CalibrationPoses poses;	
	generate_poses(poses, mfpc, cb, config.nposes, config.min, config.max);
	
	display(cb); display(poses);
	
	CalibrationPosesConfig cfg_poses;
	cfg_poses.poses().resize(poses.size());
	
	PlateConfig refpl = cfg_scene.plates()[0];
	PlatesConfig cfg_plates; cfg_plates.reserve(config.nposes);
			
	Pose ref; ref.translation() << -cb.pitch(), 0.;
	
	int j=0;
	for(const auto& [p, f] : poses) {
		Pose pc = to_coordinate_system_of(p, ref);
	
		DEBUG_VAR(f); DEBUG_VAR(pc); 
		cfg_poses.poses()[j].pose() = pc;
		cfg_poses.poses()[j].frame() = f;
		++j;
		
		PlateConfig plcfg = refpl;
		plcfg.pose() = pc;		
		cfg_plates.emplace_back(plcfg);
	}
	
	v::save("poses-"+std::to_string(getpid())+".js", cfg_poses);
	
	cfg_scene.plates() = cfg_plates;
	v::save("scene-"+std::to_string(getpid())+".js", cfg_scene);

	wait();
////////////////////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////
	PRINT_INFO("========= EOF =========");

	Viewer::wait();
	Viewer::stop();
	return 0;
}

