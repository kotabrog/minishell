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
bash-3.2$ echo x < ttt
# bash: ttt: No such file or directory
echo x > text  a; cat text
# x a
export a="export b=c"; $a; echo $b
# c
echo x > a > b
cat a
cat b
# x