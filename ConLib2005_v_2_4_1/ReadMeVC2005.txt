                     -=* ========================== *=-
                     -=* The ConLib Console Library *=-
                     -=*  VC++ 2005 Express Edition *=-
                     -=* ========================== *=-

The ConLib library is a set of routines that offer simplified access
to the WIN32 API console manipulation functions.  All the programmer
needs to do is include the ConLib header file in any modules calling
the ConLib functions, and also make sure that the ConLib library is
included in the list of files the linker references.

This "readme" document is for users wishing to use ConLib for their
Visual C++ 2005 Express Edition projects. If you are using Visual C++
version 6, you should download the non-custom build from the website
(http://staffwww.fullcoll.edu/sedwards/ConLib/ConLibIntro.htm).



===============================================================
Steps to using the ConLib library for VC++ 2005 Express Edition
===============================================================

1) In any source code modules that use the library routines, you must
   be sure to include the ConLib header file, for example:

      #include    "ConLib.h"

   Make sure that the header file is either in the same subdirectory
   as your source code modules, or in the path the compiler searches
   for #include files.

2) The linker will need access to the ConLib library so your function
   calls can be resolved. If you are working with a makefile, simply
   add it to the list of libraries. If you are working in a Visual C++
   project, do the following:

   a) After you've created your project, bring up its properties by
      selecting "Project -> <Project Name> Properties..."

   b) In the tree control to the left, expand "Configuration
      Properties", then "Linker -> Input". To the right you should see
      a space for "Additional Dependencies"; place your cursor in this
      field and enter "ConLib2005.lib".

   c) The linker will need to locate the ConLib library file when you
      build your project.  The simplest way to achieve this is to
      place the appropriate ConLib library file in the same
      subdirectory where your source code files are located.  An
      alternate method is to place the library in the subdirectory of
      your own choosing, then updating the library path the linker
      searches (you can find this by traversing the menu path "Tools
      -> Options -> VC++ Directories". To the right you'll see a
      drop-down listbox labeled "Show directoreis for:"; select
      "Library files" and then add the location of where you wish to
      keep the ConLib2005.lib file on your system.

That's all there is to it!  Happy coding!

Scott Edwards
sedwards@fullcoll.edu
11/19/2006
