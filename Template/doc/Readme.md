# Template Module 
Template to be used for all modules within this project

1.  Decide for a name for the new module. Module names should start with uppercase and use CamelCase notation (Example: NewModule)
2.  Create a copy of the template directory. The new name must exactly match your module name (Example: cp -R Template NewModule)
3.  Add the new directory to the template without any changes to give git the chance to recognize it as copy of Template module
4.  Rename the files in src and source directory according to new module's name. Filename should use CamelCase notation but start with a lowercase letter. (Example: template.c -> newModule.c, template.h -> newModule.h)
5.  Change the content of all .c and .h files and replace template with the new module's name
6.  Change make/Makefile, replacing template with the new module's name
7.  Add the new module to the project Makefile by adding it to MODULES variable
