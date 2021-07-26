#!/bin/bash

exe="./src/scene/scene"
path="../examples"

camera="${path}/camera.js"
scene="${path}/scene.js"

${exe} \
	--pcamera "${camera}" \
	--pscene "${scene}" \
	--gui true \
	--verbose true -l 15 \
	--nposes 10 \

