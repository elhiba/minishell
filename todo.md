# To do

## Parsing
- new parsing letter by letter, handle pipes/redirects(dont care about space) , stops while not in quotes or when space 
- quotes care only about space = hi"test"hi ah -> hitesthi ah  and 
- handle errors
- handle variable expansion while not in s quotes , wrong vars turn to ''
- handle $? , replace it literally anywhere , while not in s quotes = test$?yes -> test127yes

- " wehfuw > outfile1 >  outfile2"  creates outfile1/2 no matter what


## Exec
- handle exit status (add in struct maybe)


🧩 Core Left To-Do (Mandatory Part):

🔁 1. Pipelines
	Handle ls | grep foo (use pipe(), dup2(), fork() chains)

📦 2. Redirections
	> for output

	< for input

	>> for append

	<< for heredoc (requires handling SIGINT differently)

👻 3. Signals (advanced)

	Heredoc-specific signal behavior

🔚 5. Exit status
	Update $? correctly

	Return correct code on builtin/command failures

🪙 Bonus Ideas (if you're going for more):
	&&, || logic

	*, ?, etc. wildcards (globbing)

	Advanced quoting

	Variable expansion ($HOME, $USER)

	() subshell grouping