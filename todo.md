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
- handle envirenement updates
- complete cd(update env) - exit(args) - export - unset