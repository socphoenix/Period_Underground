# Period_Underground

<b><u><i>This app is now available on the Play Store!</b></u></i>


Period Tracker that keeps all data on device
This app is a basic QT 6.3 app that works on Windows and Android. It should also compile for Linux and macOS using QT Creator open source editions. The app works to locally store period data and estimate when the next period will be. It does not track fertility, and should not be used as a way to track the Rythm method, Natural Family Planning, or other forms of birth control to prevent pregnancy. It is released under the GNU Public License V3.
The app uses shades of red to show bleeding, grey for spotting, and green for the next expected period.

![image](https://user-images.githubusercontent.com/18272432/176724435-c08d61c0-8dc4-462e-96a7-03bd83dcb3e4.png)
![Screen Shot 2022-07-07 at 12 09 13 PM](https://user-images.githubusercontent.com/18272432/177840774-0353bc60-951d-436d-9a4f-2d7aa422108b.png)
![Screenshot_2022-07-09-11-45-53](https://user-images.githubusercontent.com/18272432/178116792-f0eaa7f4-510c-43a9-b8dd-63471294e44f.png)


Notes on Database usage/encryption:
While the Google Play Store download has encryption libraries in it, none of the programs for download here have it to make certain this repo is in compliance with export laws. You will need to build it from source, which you can find here: https://github.com/devbean/QtCipherSqlitePlugin

Library license info:
This has been put in front of building instructions due to the number of developers whose open source contributions helped make this app possible.

<b><u>Qt libraries used are Core, GUI, and SQL</u></b> which are licensed under the GNU Lesser Public License v3 https://www.gnu.org/licenses/lgpl-3.0.html .  The Qt source code for all of these libraries can be downloaded from https://download.qt.io/official_releases/qt/6.3/6.3.2/single/ . Alternatively you can contact me here on github or at tuc03516@gmail.com for a copy of the source code.

<b><u>SQlite</u></b> is licensed under the public domain. It's source code can be found at https://sqlite.org/src/doc/trunk/README.md .

<b><u>QtCipherSqlitePlugin library</u></b> is released under the GNU Lesser General Public License Version 2.1 and code can be found at https://github.com/devbean/QtCipherSqlitePlugin .

<b><u>wxSQLite3 is used by QtCipherSqlitePlugin</u></b> and is licensed under the WxWindows Library License. Source code for wxSQlite3 can be found at https://utelle.github.io/wxsqlite3/docs/html/index.html .

<b><u>SQLite3 Multiple Ciphers is used by QtCipherSqlitePlugin</u></b> and is released under the MIT license. Source code for this project can be found at https://utelle.github.io/SQLite3MultipleCiphers/
  
<b><u>Building Instructions.</u></b>
While this can be compiled on the command line it will be much simpler to use the tools Qt provides. The onine installer can be found at https://www.qt.io/download-qt-installer.

Make sure to install cmake using this tool. From here you can either set up qt creator to build for your architecture (recommended) as well as for other devices like Android. Due to US Export laws this program cannot be sent in compiled form. In order to get the library needed you will need to compile it. There are directions at https://github.com/devbean/QtCipherSqlitePlugin , and can be downloaded from them or from my forked repository at https://github.com/socphoenix/QtCipherSqlitePlugin . Once compiled it will need to go into your Qt installation folder. For instance for macOS go to your Qt installation folder/6.3.2/macos/plugins/sqldrivers. Once this step is done from Qt Creator select Open Project and navigate to the folder containing the source code of this project. Select CMakeLists.txt, and click Open. QT Creator will ask to adjust CMake to match your current configurations. Press ok and follow the guide. This will allow you to select run or build to create the executable file for your current computer/device. Once the program is compiled use the deployment tool for your chosen system.
Windows: https://doc.qt.io/Qt-5/windows-deployment.html
MacOS: https://doc.qt.io/qt-6.2/macos-deployment.html
Android: https://doc.qt.io/qt-6/deployment-android.html

Compiling by command-line:
Example uses Windows.
using CMake use the following command on windows to compile using the QT open-source tools (example is for QT 6.3.2):
"cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.3.2\msvc2019_64 -S <source-dir> -B <build-dir>"


To install on Android:
In order to install these you will need to allow unknown apps, see [here for more info.](https://android.gadgethacks.com/how-to/android-101-sideload-apps-by-enabling-unknown-sources-install-unknown-apps-0161947/)

Library license info:
Qt Libraries used are Core, GUI, SQL, and are licensed under the GNU Lesser Public License v3 https://www.gnu.org/licenses/lgpl-3.0.html .  The Qt source code for these libraries can be downloaded from https://download.qt.io/official_releases/qt/6.3/6.3.2/single/ . Alternatively you can contact me here on github or at tuc03516@gmail.com for a copy of the source code.
SQlite is licensed under the public domain.

