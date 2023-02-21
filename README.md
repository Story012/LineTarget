# EML6805
Projects for Advanced Design of Robots course

# LineFollower:

There are two main executables, one for an image and one for a video file/live camera.

Go to your preffered directory in a terminal, 
```
cd ~/Documents/robotics_is_life
```

Download the files:
```
// Grab files from github; note this will download in your current directory!
git clone https://github.com/Story012/EML6805.git

cd LineFollower
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
./lineFollower
```
or 
```
./lineFollower_live
 ```

## VSCode approach:
```
cd LineFollower
code .
```

After VSCode is opened, hit build and run either executable.
