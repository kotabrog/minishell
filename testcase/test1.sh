export x=a| |echo a
# bash: syntax error near unexpected token `|'
exho a  >> >
# bash: syntax error near unexpected token `>'
export a="text" ; echo hello > $a ; cat text
# hello
export a="text test" ; echo hello > $a
# bash: $a: ambiguous redirect
export a="text test" ; echo x < $a
# bash: $a: ambiguous redirect
echo x > $?
echo x >> $?
echo x < $?
# x
echo x < ttt
# bash: ttt: No such file or directory
echo x > text  a; cat text
# x a
export a="export b=c"; $a; echo $b
# c
echo x > a > b
cat a
cat b
# x
export a=" "
echo$a-a
# -a
echo"$a"-a
# bash: echo -a: command not found
echo'$a'-a
# bash: echo$a-a: command not found