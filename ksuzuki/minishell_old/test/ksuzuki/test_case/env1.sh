mkdir temp
cd temp
touch test
export ls_s=ls
$ls_s
export a="b=c"
$a
export p=q=r
$p
$q
export pipe="|"
echo a $pipe grep a
export ec=echo
$ec a
export ex=export
$ex sample=abc
echo $sample
$aaaaaa echo a
export yazi=>
export koro=;
echo $koro
export koro=";"
echo $koro a
export n=-n
echo $n abc
echo abc
