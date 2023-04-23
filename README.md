This repository holds all the code necessary for a custom impementation of simple UNIX shell. The simple shell handles the executions of executables found in the environmental variable PATH, with or without their full paths. Sample commands that our shell supports include ls (/bin/ls), pwd, echo, which, whereis, etc.
The following shell bulletins have also been created:
1. exit -  exits shell (Usage: exit [status]
2. env -  prints environmental variables (Usage: env)
3. setenv -  creates or modifies an environmental variable (Usage: setenv name value)
4. unsetenv -  removes an envrionmental variable (Usage: unsetenv name value)
5. cd -  changes directories (Usage: cd [-][~][path])
6. It also handles aliases, pipelines, and redirections.

AUTHORS: @David T, @Maxwell A
