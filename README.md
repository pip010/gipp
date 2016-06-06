# gipp
General Image Procesing Pipelines



# Example

The following example will give you and idea how to use the single header only **gipp.hpp**

```
typedef Image<unsigned char,3> ImageType;

gpipe<ImageType,
ScopedPointer< ImageFileReader<ImageType> >,
ScopedPointer< BinaryDilateImageFilter< ImageType, ImageType, typename dilate_pipe_args<ImageType>::StructuringElementType > >,
ScopedPointer< ImageFileWriter<ImageType> >
> pipe;

dilate_pipe_args<ImageType> args;
```

# Building

The **gipp** library is a header only lib ready to be used by directly including the header file **src/gipp.hpp** . However, to use the toolset of CLI utility apps you do need to use cmake and build. For convenience building in Linux **build.sh** script is available.

```
For QtCreator importer to work pass those during cmake gneration step:

-DCMAKE_BUILD_TYPE=Debug -DITK_DIR=/home/username/ITK-4.9.0_BUILD

The CLI tool depends on the command args parsing library TCLAP http://tclap.sourceforge.net/
```
