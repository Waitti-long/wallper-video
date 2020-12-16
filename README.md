# wallper-video
 play video on wallper

### Usage

**First, You Should Install ffplay(ffmpeg common contain it) and Add it To Your *Environment Variable***

**Second, Compile or Use Compiled Version**

```sh
# g++ main.cpp -o wallper-video.exe
wallper-video.exe <Filename> [ffplay arguments] # ffplay arhuments is the ffplay argument, you can use it to specify video size like 1920x1080.
# sample
wallper-video.exe sample.mp4
wallper-video.exe sample.rgb "-video_size 1920x1080"
```

### Principle
Just run ffplay and use the window as a child window of the desktop wallpaper.

### Bug
When terminate the program, it may not switch back to the original wallpaper, you can restart explorer.exe to fix this bug.