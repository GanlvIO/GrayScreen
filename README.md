# GaryScreen

A simple topmost transparent gray window to decrease screen brightness

## Usage

Start it. You can close it in task manager.

## Compile

Yes! Just **ONE** c-source file!  

Just start an new empty WIN32EXE project in Visual Studio, paste the main code and change the constant. Then compile it.

### Build with MinGW GCC

You can build it with MinGW GCC. This environment is quite smaller than Visual Studio.

```bash
gcc main.c -mwindows -DWINVER=0x500 -lgdi32 -oGrayScreen.exe
```

## LICENSE

[MIT](https://opensource.org/licenses/MIT)
