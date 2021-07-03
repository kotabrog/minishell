/bin/ls
/bin/ls -la
echo $?
/bin/ls file
echo $?
expr $? + $?

ctrl+C
ctrl+\
ctrl+D # 改行される
aaactrl+C
aaactrl+D
aaactrl+\
cat
ctrl+C
cat
ctrl+\  #Quit: 3がない
cat
ctrl+D

echo 'abc'
echo ''
echo '$HOME'
echo ' ' a
echo '|' echo x '>' file

env

export a=b
export PWD=x
env

unset a PWD
env

cd srcs/
/bin/ls
cd main.c
cd file
cd .
/bin/ls
cd ..
/bin/ls

pwd
cd srcs/
pwd

../minishell
ctrl+D

ls
unset PATH
ls
ctrl+D
./minishell
cp minishell ls
export PATH=$PWD:/bin
ls
ctrl+D
ctrl+D
./minishell

ls > file
cat < file
ls >> file
cat < file
ls < fil < fil
cat << a
x
$?
d
a

cat file | grep Makefile | more
ls -la | wc -l
sadsadasda | ls | ls
ls > file | ls -la | cat
cat file

echo xctrl+C
enter
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

echo $?
echo $a
echo "$?"
env | grep USER
echo $USER
