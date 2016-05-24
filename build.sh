if [ "$#" -gt 0 ]; then

	if ! [ -d "build" ]; then
		mkdir bin
	fi
	
	(cd bin; cmake -DITK_DIR="$1" ../ && make )
	
else
	echo "Pass a path to thr ITK_DIR as first argument, Please ;)"
fi
