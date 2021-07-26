#!/bin/bash

exe="./src/prism/prism"
path="../examples"

camera="${path}/camera.js"
scene="${path}/plates.js"

${exe} \
	--pcamera "${camera}" \
	--pscene "${scene}" \
	--gui true \
	--verbose true -l 15 \
	--nrays 0 \
	--save_all true \
	--run_all true \

