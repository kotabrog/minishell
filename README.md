# minishell

## Overview

It's a small bash.

## Requirement

- readline libraries

If necessary, install as follows

```
sudo apt-get install libreadline-dev
or
yum install readline-devel
or
brew install readline
```

## Usage

```
git clone https://github.com/kotabrog/minishell.git
cd minishell
make
./minishell
```

Now you can experience the little shell.

## Features

minishell combines the following features.

- Run the executable file
- Maintaining environment variables
- Exploring the PATH
- echo [-n]
- cd
- pwd
- export
- unset
- env
- exit
- | ; < << > >> ' "
- $? $characters
- ctrl+C ctrl+\ ctrl+D
- history (not command)

## Reference

- Overall composition
  - [nfukada's slide](https://docs.google.com/presentation/d/1c2PU6ZST7uMwNHl6aAz2WsJ5QFf1J7JJsMkW0VSTXc8/edit#slide=id.p)
  - https://brennan.io/2015/01/16/write-a-shell-in-c/
  - https://diary.shuichi.tech/entry/2017/03/31/225633
  - http://www.coins.tsukuba.ac.jp/~yas/coins/literacy-2018/2018-06-08/

- fork
  - https://kaworu.jpn.org/c/%E3%83%97%E3%83%AD%E3%82%BB%E3%82%B9%E3%81%AE%E4%BD%9C%E6%88%90_fork

- signal
  - https://qiita.com/supaiku2452/items/10772cbd2706dede06b9
  - https://www.atmarkit.co.jp/ait/articles/1708/04/news015.html

- pipe
  - https://qiita.com/edo_m18/items/989d2907d4627e19ff65
  - https://qiita.com/genzouw/items/87f8db46cebc8c4f9ae7

- environment variable
  - https://qiita.com/angel_p_57/items/480e3fd4552e52199835
  - https://qiita.com/privativealpha/items/606816827e2e62995194
  - https://qiita.com/kure/items/f76d8242b97280a247a1
  - https://www.webzoit.net/hp/it/internet/homepage/env/cs/server/os/type/unix/linux/shell/kind/sh_bash/environment/

## Author

kota (ksuzuki)： [twiter](https://twitter.com/Kotabrog)

tkano

## Licence

[MIT](https://github.com/kotabrog/minishell/blob/main/LICENSE)
