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

I will install the next tools:
> - clang-format
> - cppstyle
> - gdb

##### MacOS
**CMAKE**
0 Go to **Preferences > C/C++ > Environment**
1 Click **Add**
2 Name **PATH**
3 Value **/usr/local/bin**
4 Click **Ok**

**Code style and auto-format**
In terminal:
> brew install clang-format

> clang-format -style=WebKit -dump-config > **<your-project-root-directory>**/.clang-format

The second line will produce the hidden file at root level of your project directory,
so every **.cpp** file will use the same format.

See **clang-format --help** for more information.

**Debugger**
In terminal:
> brew install gdb
> echo "set startup-with-shell off" >> ~/.gdbinit

##### Universal part
**Code Style and auto-format**
In Eclipse, go to **Help > Eclipse Marketplace** and search for _CppStyle_ by _Zhanwei Wang_, install it.

After Eclipse restart, go to **Preferences > C/C++ > CppStyle**,
select your _clang-format_ installation path in **Clang-format path** field.

You can find it by typing in terminal:
> which clang-format

You might want to tick **Run clang-format on file save**.

Than, switch to **Code Style > Formatter** tab, and change **Code Formatter** option to **CppStyle (clang-format)**.
