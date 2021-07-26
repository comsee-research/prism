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
	PRINT_INFO("========= PRISM: Plenoptic Raw Image Simulator =========");
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
		
	DEBUG_ASSERT((cfg_scene.plates().size() > 0u), "No model provided.");
	Plates scene;
	scene.reserve(cfg_scene.plates().size());	
	for (const auto& plate_cfg : cfg_scene.plates()) scene.emplace_back(plate_cfg);
			
////////////////////////////////////////////////////////////////////////////////	
	PRINT_WARN("Generating images...");
	display(mfpc);
	int i = 0; 
	for (const auto& obj : scene)
	{
		display(obj);
		
		PRINT_DEBUG("Obj (" << obj.width() << ", " << obj.height() << ") at p = \n" << obj.pose());		
		Image raw;
		
		//wait();
		
		PRINT_INFO("========= Start image ("<< i << ") generation...");	
		auto t_start = std::chrono::high_resolution_clock::now();			
		{
			//if (mfpc.multifocus()) generate_image(raw, mfpc, obj, config.nrays, config.vignetting);
			//else generate_image(raw, mfpc, obj, (mfpc.I() > 0));
			
			generate_image(raw, mfpc, obj, config.nrays, config.vignetting);
		}
		auto t_end = std::chrono::high_resolution_clock::now();
		const double computational_time = std::chrono::duration<double>(t_end-t_start).count();
		
		PRINT_INFO("========= Image generation finished (in "<< computational_time << " s)!");	
	#if 0	
		PRINT_INFO("========= Displaying generated image =========");
		RENDER_DEBUG_2D(
			Viewer::context().layer(Viewer::layer()++).name("Raw plenoptic image"), 
			raw
		);
	#endif
		
		if (config.run_all or save())
		{
			cv::imwrite("image-"+std::to_string(getpid())+"-"+std::to_string(i)+".png", raw);	
		}
		
		++i;
	}	
////////////////////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////
	PRINT_INFO("========= EOF =========");

	Viewer::wait();
	Viewer::stop();
	return 0;
}

