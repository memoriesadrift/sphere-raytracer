# How to run:
In the root folder compile with `make`
Then you can run the produced executable however you wish, specifying the input file path with the `-f` flag, such as: `./raytracer.x -f scenes/example1.xml`
Alternatively, you can generate output files for examples 1 through 3 by running `make exec` in the project root.

You can also get rid of objects files with `make clean`, artifacts (ppms and executables) with `make clean-artifacts` or everything with `make full-clean`

# Input Specs
The raytracer takes XML files describing the scene it should render as input, adhering to [this specification](http://vda.univie.ac.at/Teaching/Graphics/22s/Labs/Lab3/lab2_file_specification.html).

# Additional and General Remarks

The main reason for choosing C was to explore procedural programming and its patterns and methods in larger projects, so I deliberately chose to avoid OOP.

My code should compile on any machine with gcc and make installed.
I tried to adhere to [this style guide](https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html) while programming.

