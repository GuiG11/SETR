**Preparing the compilation environment**

In a terminal, enter the base directory of your project, create the build directory, and use cmake to prepare make

```
cd SETR/Trab1
cd mkdir build
cd build
cmake ../src
make
./main
```

**Generating documentation**
The code is documented in doxygen. So, you can easily generate html documentation pages.

```
cd doc
doxygen
```
Then, you can display the pages running (inside the doc directory)

firefox html/index.html &
Of course, you can replace firefox with your favourite browser.
