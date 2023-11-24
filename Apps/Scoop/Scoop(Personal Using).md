# 常用指令

| Command | Summary |
| ------- | ------- |
|alias|      Manage scoop aliases|
|bucket  |   Manage Scoop buckets|
|cache  |    Show or clear the download cache|
|cat    |    Show content of specified manifest.|
|checkup |   Check for potential problems|
|cleanup |   Cleanup apps by removing old versions|
|config  |   Get or set configuration values|
|create  |   Create a custom app manifest|
|depends |   List dependencies for an app, in the order they'll be installed|
|download|   Download apps in the cache folder and verify hashes|
|export  |   Exports installed apps, buckets (and optionally configs) in JSON format|
|help    |   Show help for a command|
|hold    |   Hold an app to disable updates|
|home    |   Opens the app homepage|
|import  |   Imports apps, buckets and configs from a Scoopfile in JSON format|
|info    |   Display information about an app|
|install |   Install apps|
|list    |   List installed apps|
|prefix  |   Returns the path to the specified app|
|reset   |   Reset an app to resolve conflicts|
|search  |   Search available apps|
|shim    |   Manipulate Scoop shims|
|status  |   Show status and check for new app versions|
|unhold  |   Unhold an app to enable updates|
|uninstall|  Uninstall an app|
|update   |  Update apps, or Scoop itself|
|virustotal| Look for app's hash or url on virustotal.com|
|which     | Locate a shim/executable (similar to 'which' on Linux)|

## Search

Show available apps:
```scoop
scoop search <name>
scoop search python
```

Then it will show something like:
```scoop
Name      Version  Source Binaries
----      -------  ------ --------
python    3.12.0   main
winpython 3.11.5.0 main
```
## Install

1. Downloading Python:
```scoop
scoop install <app-name>
scoop install python
```

Then it will show something like:
```scoop
Installing 'dark' (3.11.2) [64bit] from main bucket
dark-3.11.2.zip (3.5 MB) [====================================================================================] 100%
Checking hash of dark-3.11.2.zip ... ok.
Extracting dark-3.11.2.zip ... done.
Linking D:\Scoop\apps\dark\current => D:\Scoop\apps\dark\3.11.2
Creating shim for 'dark'.
'dark' (3.11.2) was installed successfully!
Installing 'python' (3.12.0) [64bit] from main bucket
python-3.12.0-amd64.exe (25.3 MB) [===========================================================================] 100%
Checking hash of python-3.12.0-amd64.exe ... ok.
Running pre_install script...
Running installer script...
Linking D:\Scoop\apps\python\current => D:\Scoop\apps\python\3.12.0
Creating shim for 'python3'.
Creating shim for 'idle'.
Creating shim for 'idle3'.
Persisting Scripts
Persisting Lib\site-packages
Running post_install script...

'python' (3.12.0) was installed successfully!
Notes
-----
Allow applications and third-party installers to find python by running:
"D:\Scoop\apps\python\current\install-pep-514.reg"
```
As you can see, the scoop installed "dark" first and then Python. Pay attention to the last line -- It shows where you can find Python.

2. Install git
```scoop
scoop install git
```

Then it will show something like:
```scoop
Installing '7zip' (23.01) [64bit] from main bucket
7z2301-x64.msi (1.8 MB) [=====================================================================================] 100%
Checking hash of 7z2301-x64.msi ... ok.
Extracting 7z2301-x64.msi ... done.
Linking D:\Scoop\apps\7zip\current => D:\Scoop\apps\7zip\23.01
Creating shim for '7z'.
Creating shim for '7zFM'.
Creating shim for '7zG'.
Creating shortcut for 7-Zip (7zFM.exe)
Persisting Codecs
Persisting Formats
Running post_install script...
'7zip' (23.01) was installed successfully!
Notes
-----
Add 7-Zip as a context menu option by running: "D:\Scoop\apps\7zip\current\install-context.reg"
Installing 'git' (2.43.0) [64bit] from main bucket
PortableGit-2.43.0-64-bit.7z.exe (53.8 MB) [==================================================================] 100%
Checking hash of PortableGit-2.43.0-64-bit.7z.exe ... ok.
Extracting dl.7z ... done.
Linking D:\Scoop\apps\git\current => D:\Scoop\apps\git\2.43.0
Creating shim for 'sh'.
Creating shim for 'bash'.
Creating shim for 'git'.
Creating shim for 'gitk'.
Creating shim for 'git-gui'.
Creating shim for 'scalar'.
Creating shim for 'tig'.
Creating shim for 'git-bash'.
Creating shortcut for Git Bash (git-bash.exe)
Creating shortcut for Git GUI (git-gui.exe)
Running post_install script...
'git' (2.43.0) was installed successfully!
Notes
-----
Set Git Credential Manager Core by running: "git config --global credential.helper manager"

To add context menu entries, run 'D:\Scoop\apps\git\current\install-context.reg'

To create file-associations for .git* and .sh files, run 'D:\Scoop\apps\git\current\install-file-associations.reg'
```