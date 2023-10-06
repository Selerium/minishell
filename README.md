# minishell
42AbuDhabi project that entails creating a miniature shell terminal.fix 
fix herdoc  for this case "<<a

fix "env -i minishell" (enters without env variables)
and fix when no env variables and exporting 

and double check the way you did the prompt  (getCWD)
and start testing again maybe
also check "export"

check running commands without any arguments 
- handle exit codes 
- handle seg faults
- handle returns

<!-- check exit codes for sytax errors (exit code should always be 258 for syntax error) -->

<!-- when theres syntax error, exit code is always zero -->

cd | ... : gets a double free
pwd edge case: create a directory, go inside and delete created directory. PWD should show the same path.
