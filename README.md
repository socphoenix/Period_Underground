# Period_Underground
THIS IS A WORK IN PROGRESS. CODE IS NOT READY TO DEPLOY.

Period Tracker that keeps all data on device
This app is a basic QT 6.3 app that works on Windows and Android. It should also compile for Linux and macOS using QT Creator open source editions. The app works to locally store period data and estimate when the next period will be. It does not track fertility, and should not be used as a way to track the Rythm method, Natural Family Planning, or other forms of birth control to prevent pregnancy. It is released under the GNU Public License V3.
The app uses shades of red to show bleeding, grey for spotting, and green for the next expected period.

![image](https://user-images.githubusercontent.com/18272432/176724435-c08d61c0-8dc4-462e-96a7-03bd83dcb3e4.png)
![image](https://user-images.githubusercontent.com/18272432/176724619-78065ebf-b2cd-4983-9cec-b4918c65e777.png)
![image](https://user-images.githubusercontent.com/18272432/176724699-6e4a29c7-22a9-4069-bc76-756249c67ee4.png)

Notes on Database usage/encryption:
This program uses sqlite, which as noted in the release packages does not support encryption of the database. On Mobile the database is stored within the programs sandbox to ensure other apps can't see the database. It may be possible for file explorers like Google Files to locate this database on Android with enough dedication. On desktop versions the database is stored in the User's Documents folder. In either case in order for someone to access the database they would require access to the device the database is stored on. In order to make sure the data stays as secure as possible please keep your device up to date with security updates and only trust your device with trustworthy individiuals to minimize risk. In a future release I would like to add encryption to the database itself but this adds complications specifically with keeping the code open source due to U.S. export laws. As I am just a hobbyist and not someone with a ton of experience in this field I cannot even begin to estimate when such a feature could be added. In the meantime I highly recommend using whole device encryption to protect your device against theft/unauthorized access, and recommend keeping the device up to date and limiting others access to the device to minimize the risk of data getting into the wrong hands. 

Library license info:
This has been put in front of building instructions due to the number of developers whose open source contributions helped make this app possible.

<b><u>Qt libraries used are Core, GUI, and SQL</u></b> which are licensed under the GNU Lesser Public License v3 https://www.gnu.org/licenses/lgpl-3.0.html .  The Qt source code for all of these libraries can be downloaded from https://download.qt.io/official_releases/qt/6.3/6.3.1/single/ . Alternatively you can contact me here on github or at tuc03516@gmail.com for a copy of the source code.

<b><u>SQlite</u></b> is licensed under the public domain. It's source code can be found at https://sqlite.org/src/doc/trunk/README.md .

<b><u>QtCipherSqlitePlugin library</u></b> is released under the GNU Lesser General Public License Version 2.1 and code can be found at https://github.com/devbean/QtCipherSqlitePlugin .

<b><u>wxSQLite3 is used by QtCipherSqlitePlugin</u></b> and is licensed under the WxWindows Library License. Source code for wxSQlite3 can be found at https://utelle.github.io/wxsqlite3/docs/html/index.html .

<b><u>SQLite3 Multiple Ciphers is used by QtCipherSqlitePlugin</u></b> and is released under the MIT license. Source code for this project can be found at https://utelle.github.io/SQLite3MultipleCiphers/
  
Building Instructions.
TODO
You will need the QT online installer, which can be found here: https://www.qt.io/download-qt-installer
Make sure to install cmake using this tool. From here you can either set up qt creator to build for your architecture (recommended) or you can use command line tools installed with the package to build the program. If using QT Creator, select Open Project and navigate to the folder containing the source code. Select all files, and click Open. QT Creator will ask to adjust CMake to match your current configurations. Press ok and follow the guide. This will allow you to select run or build to create the executable file for your current computer/device.

For instance on Windows you can do the following:
using CMake use the following command on windows to compile using the QT open-source tools (example is for QT 6.3.1):
"cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.3.1\msvc2019_64 -S <source-dir> -B <build-dir>"

