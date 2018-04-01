# Tools
### Installing IDE
Across all modules, I'm using [**Eclipse Oxygen**](http://www.eclipse.org/downloads/).
This IDE requires Java SE 6 to be installed on you machine.

##### MacOS
To install, I used **Homebrew**:
> brew cask install java

This command will install the latest version of Java available.
But also you might want to specify the exact version, you can do it like this:

> brew cask install java6

After that, install **Eclipse**:
> brew cask install eclipse-cpp

##### Windows
Coming soon...
##### Linux
Coming soon...

### Setting up IDE and installing extra tools
The set up process is similar for every platform, but _tools' istallation_ process might differ between different OS.

I will install and setup the next tools:
> - CMake
> - clang-format
> - cppstyle
> - cppcheck
> - debugger

##### MacOS
**CMake**
> - Go to **Preferences > C/C++ > Environment**;
> - Click **Add**;
> - Set "Name" to **PATH**;
> - Set "Value" **/usr/local/bin**;
> - Click **Ok**;

**Code style and auto-format**

In terminal:
> brew install clang-format

> clang-format -style=WebKit -dump-config > **<your-project-root-directory>**/.clang-format

The second line will produce the hidden file at root level of your project directory,
so every **.cpp** file will use the same format.

See **clang-format --help** for more information.

**Debugger**
###### GDB
In terminal:
> brew install gdb
>
> echo "set startup-with-shell off" >> ~/.gdbinit

[Further instructions](https://sourceware.org/gdb/wiki/BuildingOnDarwin)

**NOTE:**
> The scope of course covers the working with GDB debugger, **BUT** the reality is cruel ;-(...
>
> For MacOS Sierra (10.12) and higher, GDB debugger almost unuseful [(source)](http://wiki.eclipse.org/CDT/User/FAQ#How_do_I_use_GDB_on_recent_versions_of_macOS.3F),
>
> I will switch to **LLDB** debugger, which has an experimental support in Eclipse.
>
> Instructions will be added after I make it work on my machine.

###### LLDB
> - Install Xcode;
> - Make sure that you installed the Xcode CommandLineTools by doing in Terminal:
>	xcodebuild --version
>	if it shows something like
		xcode-select: error: command line tools are already installed, use "Software Update" to install updates
	Check _LLDB - XCode Fix_ section below
>


###### LLDB - XCode Fix
> xcode-select --install
> sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
> xcodebuild --version


**CppCheck**

In terminal:
> brew install cppcheck

In Eclipse:

**TO BE ADDED MODE DETAILS**

##### Universal part
**Code Style and auto-format**

In Eclipse, go to **Help > Eclipse Marketplace** and search for _CppStyle_ by _Zhanwei Wang_, install it.

After Eclipse restart, go to **Preferences > C/C++ > CppStyle**,
select your _clang-format_ installation path in **Clang-format path** field.

You can find it by typing in terminal:
> which clang-format

You might want to tick **Run clang-format on file save**.

Than, switch to **Code Style > Formatter** tab, and change **Code Formatter** option to **CppStyle (clang-format)**.
