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
echo x | a
# bash: a: command not found
echo $?
# 127
a | echo x
# bash: a: command not found
# x
echo $?
# 0
>
# syntax error near unexpected token `newline'
echo $?
# 258
/bin
# bash: /bin: is a directory
echo $?
# 126
a
# bash: a: command not found
echo $?
# 127
bash
exit 1.1
# bash: exit: 1.1: numeric argument required
echo $?
# 255
sleep 10
ctrl+C
# ^C
echo $?
# 130
echo x | exit a
# bash: exit: a: numeric argument required
echo $?
# 255
exit 1 ; echo x
# exit
sleep 5
ctrl+\
# ^\Quit: 3
sleep 5 | echo x
# x
ctrl+C
# ^C
sleep 5 | echo x
# x
ctrl+\
# ^\bash-3.2$
sleep 5 > file
ctrl+\
# ^\Quit: 3
cat file
sleep 5; sleep 5
ctrl+\
# ^\Quit: 3
ctrl+\
# ^\Quit: 3
sleep 5; sleep 5
ctrl+C
# ^C
ctrl+C
# ^C
export c="a    a"
echo $c
# a a
echo "a"$c"b"
# aa ab
export a="a"$c'b'
echo $a
# aa ab
export | grep a=
# declare -x a="aa    ab"
export | grep c=
# declare -x c="a    a"
export a="'     '"
echo $a
# ' '
export a='"     "'
echo $a
# ' '
export | grep b=
echo $b
# 
