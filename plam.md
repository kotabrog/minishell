# plan

## todo

- [x] githubを用いたファイル共有
- 全体の構成
  - [x] 読み取り
    - sleep中などに追加で打ち込んだもので、改行をしていないものは、表示はされないが残った状態になる
  - 単語分割
  - 構文解析
  - 変数展開
  - コマンド実行
  - パイプの実行
  - リダイレクト
- 機能実装
  - echo
  - echo -n
  - cd
  - pwd
  - export
    - export pipe=|はマルチラインになる（実装しなくていい）
    - export aaaはaaaで登録（中身なし）
    - export aaa=はaaa=""で登録（おそらく中身空文字列）
    - export $b=cは$bを環境変数だと認識する（このときは=は区切り文字の役割になる）
  - unset
  - env
    - export aaaで登録すると表示されない
    - export aaa=で登録するとaaa=と表示される
  - exit
  - ;
  - '(マルチラインは未対応でいい)
    - 文字が続いていると一つの文と認識される。例：aaa'aaa'
    - すべてのエスケープ文字を無視
  - "(マルチラインは未対応でいい)
    - 文字が続いていると一つの文と認識される。例：aaa"aaa"
    - $, \, バッククオートは有効（今回の課題では$のみ影響）
  - <
  - '>'
  - '>>'
  - |
  - $characters
  - $?
    - これは直後に文字が続いていても$?として解釈される
  - ctrl-C
  - ctrl-D
  - ctrl-\
  - ファイル実行
  - 実行ファイルのサーチ

## 特殊ケース
  - sleep 5 中にsleep 5を何度か打ち込んだときの挙動  
    ```
    $ sleep 5
    sleep 6 <-自分で打ち込む
    $ sleep 6 <-自動で打ち込まれる
    $
    ```


## 参考サイト

- 全体の構成
  - https://brennan.io/2015/01/16/write-a-shell-in-c/
  - https://diary.shuichi.tech/entry/2017/03/31/225633
  - http://www.tohoho-web.com/ex/shell.html
  - http://www.coins.tsukuba.ac.jp/~yas/coins/literacy-2018/2018-06-08/
  - https://nafuka.hatenablog.com/entry/2021/03/29/194200

- fork
  - https://kaworu.jpn.org/c/%E3%83%97%E3%83%AD%E3%82%BB%E3%82%B9%E3%81%AE%E4%BD%9C%E6%88%90_fork

- signal
  - https://qiita.com/supaiku2452/items/10772cbd2706dede06b9

- pipe
  - https://qiita.com/edo_m18/items/989d2907d4627e19ff65
  - https://qiita.com/genzouw/items/87f8db46cebc8c4f9ae7
  - https://haystacker.net/linux-pipe-deep-dive/

- dup
  - http://capm-network.com/?tag=C%E8%A8%80%E8%AA%9E%E3%82%B7%E3%82%B9%E3%83%86%E3%83%A0%E3%82%B3%E3%83%BC%E3%83%AB-dup

- 環境変数
  - https://qiita.com/viola/items/606816827e2e62995194
  - https://qiita.com/angel_p_57/items/480e3fd4552e52199835
  - https://qiita.com/kure/items/f76d8242b97280a247a1
  - https://www.webzoit.net/hp/it/internet/homepage/env/cs/server/os/type/unix/linux/shell/kind/sh_bash/environment/

- 標準入力・標準出力
  https://qiita.com/angel_p_57/items/03582181e9f7a69f8168

- クォーテーション
  - https://blog.goo.ne.jp/01_mai/e/a4f9f01fb647066d0c7eb37e8ae0a254
  - https://se-tomo.com/2019/03/01/%E3%82%B7%E3%82%A7%E3%83%AB%E3%82%B9%E3%82%AF%E3%83%AA%E3%83%97%E3%83%88%E3%81%AE%E3%82%AF%E3%82%A9%E3%83%BC%E3%83%86%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3%E3%81%AE%E3%81%82%E3%82%8C%E3%81%93%E3%82%8C/
