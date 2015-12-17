//
// Download and place this file into your git repository. 
// Rename it to '.indent.pro' (without quotes)
//
// wget http://www.phys.uconn.edu/phys2200/downloads/indent.profile.sample
// mv indent.profile.sample .indent.pro
//
// or
//
// wget http://www.phys.uconn.edu/phys2200/downloads/indent.profile.sample -O .indent.pro
//
-gnu  // base style
-bad  // force blank lines after the declarations
-bli0 // no extra indent for braces
-nlp --ignore-newlines  //useful for breaking long lines
-bls  // put braces on the line after 'struct' declaration lines
-blf  // put braces on line following function definition line
-npsl // put the type of a procedure on the same line as its name
-i4   // Set indentation level to 4 spaces
-nut  // use spaces instead of tabs
-pmt  // preserve the modification times; potentially useful -
      // to prevent 'make' from rebuilding after indenting the source

