# Code in WSL

This is a simple program that allows you to open a folder in VSCode under WSL remote connect via a simple command line call.

## Installation

1. Download the latest release from the [releases page](https://github.com/GWMCwing/Code-In-WSL/releases/latest) / Directly clone the repository / Directly compile
2. Add the executable to your path

Compilation:
```cmd
g++ -o codeWSL.exe codeWSL.cpp
```

## Usage

The program can be run via right click menu in Windows Explorer or via command line.

### __Command Line__

```cmd
codeWSL.exe [-d Distribution] <Path>
```

### __Right Click Menu__

1. Open the registry editor
2. Goto `Computer\HKEY_CLASSES_ROOT\Directory\Background\shell`
3. Add a new key with the name of your choice, `<Your Key>`
4. Goto `Computer\HKEY_CLASSES_ROOT\Directory\Background\shell\<Your Key>`
5. Create a new `String value` under the key you just created called `Icon`, set the value to the path of the icon you want to use.
6. Create a new `String value` under the key you just created called `(Default)`, set the value to the name you want to appear in the right click menu.
7. Create a new key under the key you just created called `command`
8. Goto `Computer\HKEY_CLASSES_ROOT\Directory\Background\shell\<Your Key>\command`
9. Create a new `String value` under the key you just created called `(Default)`, set the value to the path of the executable followed by `"%V"`.

Example of the final registry path:

``` md
Computer\HKEY_CLASSES_ROOT\Directory\Background\shell\CodeWSL\command
```

Example of the value for (Default):

``` cmd
:: Run with the default distribution
"C:\Custom Program\codeInWSL\codeWSL.exe" "%V"
:: Run with a specific distribution
"C:\Custom Program\codeInWSL\codeWSL.exe" -d Ubuntu-20.04 "%V"
```
