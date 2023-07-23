# pipex
-/* Liens utiles */
https://www.codequoi.com/pipe-une-methode-de-communication-inter-processus/
https://tldp.org/LDP/lpg/node11.html
https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe
https://www.youtube.com/watch?v=6xbLgZpOBi8 <-- pipe simulation
https://www.youtube.com/watch?v=Mqb2dVRe0uo <-- communication entre processus
https://www.youtube.com/watch?v=5fnVr-zH-SE <-- dup() && dup2()


./pipex file1 cmd1 cmd2 file2

$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

// each cmd needs a stdin (input) and returns an output (to stdout)

    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes
        cmd1 stdout)                           cmd2 stdin)

External functs.
• open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
