# EML6805
Project 1 for Advanced Design of Robots course

# LineTarget:

There are two main executables, one for an image and one for a video file.

Go to your preffered directory in a terminal, 
```
cd ~/Documents/robotics_is_life
```

Download the files:
```
// Grab files from github; note this will download in your current directory!
git clone https://github.com/Story012/LineTarget.git

cd LineTarget
```

## Terminal approach:

```
// Create build folder
mkdir build 
// Move into the build folder
cd build
// Set up the build folder for cmake
cmake ..
// Compile the scripts!
make
```

From here, you can run the executables from within the build folder:
```
./lineFollower_image
```
or 
```
./lineFollower_video
 ```

## VSCode approach:
```
cd LineTarget
code .
```

After VSCode is opened, hit build and run either executable.
