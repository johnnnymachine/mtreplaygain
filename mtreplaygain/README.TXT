mtreplaygain - multithreaded replaygain: a wrapper for replaygain audio file processor (for linux)

Hi, I had a a lot of mp3s to convert so I made a wrapper for replaygain to convert them quicker, using all cores of the cpu.

------------------------------------------------------------------------------------------------------------------------------
Usage:

mtreplaygain <path>

Simply enter a path and it will recursively find all of your mp3's and ogg's and attempt to run the replaygain for each file.
It also will attempt to convert id3v1 tags to id3v2 tags for usage with replaygain

------------------------------------------------------------------------------------------------------------------------------
Libraries needed:

boost_system
boost_filesystem
pthread

------------------------------------------------------------------------------------------------------------------------------
Programs needed:

replaygain
mid3v2

------------------------------------------------------------------------------------------------------------------------------
NOTE: Use at own risk!