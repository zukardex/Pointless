# Pointless

longest/longest.ino is a solution to find the farthest point put on a TFT Display
mirror/mirror.ino is a mirroring facility to mirror the images drawn on TFT, mirroring is done with respect to both horizontal and vertical axes 
mirror/mirrorX.ino is the same as the former, but the mirroring is only done with respect to horizontal axis
mirror/mirrorY.ino is the same as the former, but the mirroring is done with respect to vertical axis.
performanceEnhancer/performanceEnhancer.ino is a solution to relax the workload put on by the TFT Display on the hosting Arduino, the performance is enhanced by approximating the curves with straight lines, there by reducing the number of points stored on the memory.


This project uses some libraries from Adafruit, some changes should be done to the code, according to the display driver you are using. Calibration values also needs to be changed, in order to make it work.
