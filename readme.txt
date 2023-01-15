# Claim
  T1: (10%) Output a valid black image file
   - fully implemented
  T2: (25%) Output an image with spheres on it after ray tracing them.
   - fully implemented
  T3: (25%) Be able to read in geometry from the specified xml files. (example1.xml)
   - fully implemented
  T4: (30%) Implement basic Phong illumination and shading. (example2.xml)
   - fully implemented
  T5: (10%) Render example3.xml with shadows
   - fully implemented

# Tested Environments
OS: macOS 13.0 Ventura
Compiler: 
  Apple clang version 14.0.0 (clang-1400.0.29.202)
  Target: arm64-apple-darwin22.1.0
  Thread model: posix

alma.par.univie.ac.at:
OS: CentOS
Compiler:
  gcc (GCC) 8.5.0 20210514 (Red Hat 8.5.0-10)

# Additional and General Remarks

I programmed in C99. Yeah.
The main reason for choosing C was to explore procedural programming and its patterns and methods in larger projects, so I deliberately chose to avoid OOP.

My code should compile on any machine with gcc and make installed.
I tried to adhere to this style guide: https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

How to run:
In the root folder compile with `make`
Then you can run the produced executable however you wish, specifying the input file path with the `-f` flag, such as: `./raytracer.x -f scenes/example1.xml`
Alternatively, you can generate output files for examples 1 through 3 by running `make exec` in the project root.

You can also get rid of objects files with `make clean`, artifacts (ppms and executables) with `make clean-artifacts` or everything with `make full-clean`
