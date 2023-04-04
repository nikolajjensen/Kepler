# Kepler Programming Language
[![Linux](https://github.com/nikolajjensen/Kepler/actions/workflows/linux.yml/badge.svg)](https://github.com/nikolajjensen/Kepler/actions/workflows/linux.yml)

This project aims to be an implementation of the APL programming language created by Kenneth E. Iverson in the late 1950's.

Below is an example of [Conway's Game of Life](https://aplwiki.com/wiki/Conway%27s_Game_of_Life) in Kepler.

```apl
⍝ A Game of Life!

⍝ Setting up a 10x10 board.
glider ← 3 3⍴1 1 1 1 0 0 0 1 0
board ← ¯10 ¯10↑glider

⍝ The function of life.
Life ← {1 ⍵∨.∧3 4=⊂+/,¯1 0 1∘.⊖¯1 0 1∘.⌽⊂⍵}

⍝ Helpers for updating the board.
Update ← {board ← Life board}
Round ← {Update ◊ ⎕←'\n \n' ◊ ⎕←board}

⍝ Run 5 rounds.
(Round⍣5)0
```



## Using Kepler
If you have the compiled binary (see next section), simply execute the following command to enter the REPL:

    ./Kepler

You can also execute a specific ``.kpl`` file by running:

    ./Kepler /path/to/file.kpl

Lastly, it is also possible to run the automatic test suite by executing:

    ./Kepler --test

## Build instructions
Kepler has been tested on Linux, macOS, and Windows. Please see below for detailed instructions for your platform.

### Dependencies
CMake requires an installation of Git to be available. This is required to automatically fetch dependencies required to build Kepler.

### macOS and Linux
After downloading the source code, compile it using CMake, as follows:
1. Ensure you are in the root folder of the downloaded project. This is the folder which contains the ```CMakeLists.txt``` file.
2. Execute ```cmake -B ./build -DCMAKE_BUILD_TYPE=Release```
3. Execute ```cmake --build ./build --config Release```
4. After compilation ends, the ```Kepler``` and ```KeplerBench``` binaries can be found inside ```/build```.

### Windows
Windows users should ensure they have GCC installed, as Kepler currently does not compile with MVSC. These instructions have been tested only with GCC 12.2.0, which can be downloaded [here](https://winlibs.com/). To ensure that GCC is selected as the compiler, ensure that the ```Path``` has the ```/bin``` directory of MinGW appended.

After downloading the source code, compile it using CMake, as follows:
1. Ensure you are in the root folder of the downloaded project. This is the folder which contains the ```CMakeLists.txt``` file.
2. Execute ```cmake -B ./build -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"```
3. Execute ```cmake --build ./build --config Release```
4. After compilation ends, the ```Kepler``` and ```KeplerBench``` binaries can be found inside ```/build```.

## Reporting issues
If you encounter any issues with Kepler while using it, please report them under issues. Please make sure you include as much detail about the error (and what you did to cause it), so it can be fixed.

## Contributing
All pull requests are welcome, so feel free to contribute!