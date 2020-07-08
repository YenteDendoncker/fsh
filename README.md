Ever wanted to open files relative to an executable instead of relative to your current working directory?
Or perhaps you don't know if the files you are looking for are located in the current working directory or
in the executable directory. Fear no more. fsh exposes a function fsh_env_fopen() that will to just that.

fsh_env_fopen() returns a FILE*, just as the regular fopen() would do.
fsh_env_fopen is called as fsh_env_fopen(filepath, mode, env_amount, envs..).
* filepath is a path to the required file, either absolute, relative to the current working directory or relative to the current executable directory.
* mode is the mode for opening the file such as "r" for read mode.
* env_amount is the amount of sub-environments given as argument (see next)
* envs... is a number of (optional) environments that should be checked besides the executable directory and working directory (see example).
The behaviour of fsh_env_fopen depends on wheter the filepath and environments
are absolute filepaths or relative filepaths.

Evaluation order (examples linux):

fsh_env_fopen("/test/file", "r", 0)
If the first argument is an absolute filepath fsh_env_fopen will for a file at this absolute filepath. Any environments if given will be ignored.
* Checks for "/test/file".

fsh_env_fopen("test/file", "r", 2, "/env1", "env2")
If the first argument is not an absolute filepath fsh_env_fopen will check in the following order:
1. The current working directory with the filename appended.
* Checks for "{working dir}/test/file".
2. The executable directory with the filename appended.
* Checks for "{executable dir}/test/file".
3. (a) For each environment, if the environment is an absolute filepath it will check the absolute filepath with the filename appended.
* Checks for "/env1/test/file".
3. (b) For each environment, if the environment is not an absolute filepath it
will check both the working and executable directory with the filename appended.
* Checks for "{working dir}/env2/test/file".
* Checks for "{executable dir}/env2/test/file".


