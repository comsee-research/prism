PRISM: Plenoptic Raw Image Simulator 
=====================================================

PRISM is a set of tools to generate and simulate raw images from a multifocus plenoptic camera (e.g., a Raytrix R12) based on the [libpleno].


Quick Start
===========

### Pre-requisites

The PRISM applications have a light dependency list:

 * [boost] version 1.54 and up, portable C++ source libraries,
 * [libpleno], an open-souce C++ library for plenoptic camera,
 
and was compiled on:
 * Ubuntu 18.04.4 LTS.
  
### Compilation & Test

If you are comfortable with Linux and CMake and have already installed the prerequisites above, the following commands should compile the applications on your system.

```
mkdir build && cd build
cmake ..
make -j6
```

To test the `prism` application you can use the example script from the build directory:
```
./../examples/run_prism.sh
```

Applications
============

### Configuration

All applications use _.js (json)_ configuration file. The path to this configuration files are given in the command line using _boost program options_ interface.

**Options:**

| short 	| long 			| default 			| description 								|
|-------	|------			|:---------:		|:-----------:								|
| -h 		| -\-help  		|           		| Print help messages						|
| -g 		| -\-gui  		| `true`          	| Enable GUI (image viewers, etc.)			|
| -v 		| -\-verbose 	| `true`          	| Enable output with extra information		|
| -l 		| -\-level  	| `ALL` (15)       	| Select level of output to print (can be combined): NONE=0, ERR=1, WARN=2, INFO=4, DEBUG=8, ALL=15 |
| -s 		| -\-pscene		|                	| Path to scene configuration file 			|
| -c 		| -\-pcamera 	|                	| Path to camera configuration file 		|
| -n 		| -\-nrays  	| `30`				| Number of rays per pixel					|
|  			| -\-vignetting	| `true`			| Enable vignetting effect in modelization	|
|  			| -\-run\_all	| `false`			| Run automaticaly all image generation		|
|  			| -\-save\_all	| `false`			| Save automaticaly all image 				|
| -n 		| -\-nposes  	| `10`				| Number of poses to generate 				|
| 	 		| -\-min  		| `450`				| Distance min for pose generation 			|
| 	 		| -\-max 	 	| `1900`			| Distance max for pose generation 			|

For instance to images generation:
```
./src/prism/prism -s scene.js -c camera.js --nrays 30 --vignetting false --run_all true --save_all true -v true -g true -l 7
```
  
Datasets
========

Datasets R12-A, R12-B and R12-C can be downloaded [from here](https://github.com/comsee-research/plenoptic-datasets). 
Same for R12-D, and the simulated _unfocused plenoptic camera_ dataset UPC-S.

Citing
======

If you use PRISM or [libpleno] in an academic context, please cite the following publication:

	@inproceedings{labussiere2020blur,
	  title 	=	{Blur Aware Calibration of Multi-Focus Plenoptic Camera},
	  author	=	{Labussi{\`e}re, Mathieu and Teuli{\`e}re, C{\'e}line and Bernardin, Fr{\'e}d{\'e}ric and Ait-Aider, Omar},
	  booktitle	=	{Proceedings of the IEEE/CVF Conference on Computer Vision and Pattern Recognition (CVPR)},
	  pages		=	{2545--2554},
	  year		=	{2020}
	}


License
=======

PRISM is licensed under the GNU General Public License v3.0. Enjoy!

[Ubuntu]: http://www.ubuntu.com
[CMake]: http://www.cmake.org
[CMake documentation]: http://www.cmake.org/cmake/help/cmake2.6docs.html
[git]: http://git-scm.com
[Eigen]: http://eigen.tuxfamily.org
[libv]: http://gitlab.ip.uca.fr/libv/libv
[lma]: http://gitlab.ip.uca.fr/libv/lma
[OpenCV]: https://opencv.org/
[Doxygen]: http://www.stack.nl/~dimitri/doxygen/
[boost]: http://www.boost.org/
[libpleno]: https://github.com/comsee-research/libpleno

---
