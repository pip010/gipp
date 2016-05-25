if [ "$#" -gt 0 ]; then

	if ! [ -d "bin" ]; then
		mkdir bin
	fi

	(cd bin; cmake -DCMAKE_BUILD_TYPE=Debug -DITK_DIR:PATH="$1" ../ && make )

else
	echo "Pass a path to the ITK_DIR as first argument, Please ;)"
fi
