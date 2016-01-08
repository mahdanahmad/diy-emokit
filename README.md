Installation instructions

CMAKE
Download : http://www.cmake.org/cmake/resources/software.html
Go in the download folder and execute :

To install cmake you need a working C++ compiler
sudo apt-get install g++

tar xzvf cmake-VERSION.tar.gz
cd cmake-VERSION.tar.gz
./bootstrap
make
sudo make install


MCRYPT
First install the dependencies :
sudo apt-get install libmcrypt-dev libmhash-dev git

Download : http://sourceforge.net/projects/mcrypt/files/latest/download
Go in the download folder and execute :

tar xzvf mcrypt-VERSION.tar.gz
cd mcrypt-VERSION/
./configure
make
make install


HIDAPI
First install the dependencies :
sudo apt-get install libudev-dev libusb-1.0-0-dev libtool dh-autoreconf

Download : https://github.com/signal11/hidapi/archive/master.zip
IT WILL NOT WORK if you downloaded from: hidapi-0.7.0.zip from https://github.com/signal11/hidapi/downloads or the command git clone git://github.com/signal11/hidapi.git
Extract the zip file and use the following commands :

unzip hidapid-master.zip
cd hidapid-master
./bootstrap
./configure
make
sudo make install

FFTW
You could install normal binary package from the repositories :
sudo apt-get install libfftw3-dev

or download : http://www.fftw.org/download.html 
Go in the download folder and execute :

tar xzvf fftw-VERSION.tar.gz
./configure
make
sudo make install

NOTE : CMAKE 3.3.2, MCRYPT 2.6.8, HIDAPI, FFTW 3.3.4 already available at working libs directory

PROJECT
sudo apt-get install liboscpack*
cmake .
make