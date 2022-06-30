# Period_Underground
Period Tracker that keeps all data on device
This app is a basic QT 6.3 app that works on Linux and Android. It should also compile for Windows and macOS using QT Creator open source editions. The app works to locally store period data and estimate when the next period will be. It does not track fertility, and should not be used as a way to track the Rythm method, Natural Family Planning, or other forms of birth control to prevent pregnancy. It is released under the GNU Public License V3.
The app uses shades of red to show bleeding, grey for spotting, and green for the next expected period.

![image](https://user-images.githubusercontent.com/18272432/176724435-c08d61c0-8dc4-462e-96a7-03bd83dcb3e4.png)
![image](https://user-images.githubusercontent.com/18272432/176724619-78065ebf-b2cd-4983-9cec-b4918c65e777.png)
![image](https://user-images.githubusercontent.com/18272432/176724699-6e4a29c7-22a9-4069-bc76-756249c67ee4.png)

Building Instructions.
You will need the QT online installer, which can be found here: https://www.qt.io/download-qt-installer
Make sure to install cmake using this tool. From here you can either set up qt creator to build for your architecture (recommended) or you can use command line tools installed with the package to build the program.

For instance on Windows you can do the following:
using CMake use the following command on windows to compile using the QT open-source tools (example is for QT 6.3.1):
"cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.3.1\msvc2019_64 -S <source-dir> -B <build-dir>"
