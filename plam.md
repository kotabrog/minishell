# plan

## todo

- [x] githubを用いたファイル共有
- Makefile
  - [x] プロトタイプ作成
  - 最終確認（リリンクなど）
- 全体の構成
  - [x] 読み取り
    - sleep中などに追加で打ち込んだもので、改行をしていないものは、表示はされないが残った状態になる
  - [x] 単語分割
    - [x] 区切り文字: ; < > >> |
    - [x] 文字列のつながり：クオート系でつながってるものは一つとみなす, $もここではそのまま文字として扱う
  - [x] 構文解析
  - 変数展開
    - [x] 変数展開の大枠の実装
    - 環境変数のサーチ
  - [x] コマンド実行
    - [x] おおまかな実装
    - [x] minishell内で./minishellを実行したときのバグの修正（fork時のシグナルの受け取りについて）
  - [x] パイプの実行
  - [x] リダイレクト
  - 入力文字数等の制限
    - [x] 標準入力→10000文字まで耐えられた（制限いらない？）
    - fileの数
    - 環境変数の数
    - 環境変数の長さ
    - 環境変数の値の長さ
    - pipeの数
    - セミコロンの数
    - pathの長さ
    - [x] file名の長さ→redirect, touchなどで確認。OK
- 機能実装
  - [x] echo
  - [x] echo -n
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
    - [x] 第一引数が数字ではないと、以下のようなエラーが出てbashを終了し、終了ステータスを255に設定する  
    `bash: exit: a: numeric argument required`
    - [x] 第一引数が数字で、第２引数以降が設定されていると、以下のエラーを出して、終了ステータスを1にし、終了しない  
    `bash: exit: too many arguments`
    - [x] とりあえずint値を受け取れるようにする
    - exit に与えられる値はLLONG_MIN~LLONG_MAX（その範囲を超えると、数字でないときと同じエラーが出る）
    - [x] exit に数字を与えるとき、末尾の0以外、先頭の0は無視される
    - [x] 正常にexitが動作した場合、引数が与えられていれば、その値を終了ステータスとして、終了する
    - [x] 正常にexitが動作した場合、引数がない場合、そのときの終了ステータスで終了する
  - [x] ;
  - [x] '(マルチラインは未対応でいい)
    - [x] 文字が続いていると一つの文と認識される。例：aaa'aaa'
    - [x] すべてのエスケープ文字を無視
  - [x] "(マルチラインは未対応でいい)
    - [x] 文字が続いていると一つの文と認識される。例：aaa"aaa"
    - [x] $, \, バッククオートは有効（今回の課題では$のみ影響）
  - [x] <
  - [x] '>'
  - [x] '>>'
  - [x] |
  - $characters
    - [x] 環境変数で使用できるのは大文字小文字アルファベットと数字で、数字から始めてはいけない。また、大文字と小文字は区別される
    - 環境変数のサーチ
  - $?
    - [x] これは直後に文字が続いていても$?として解釈される
    - [x] 簡単な実装
    - エラーパターンの精査
  - [x] ctrl-C
    - [x] 簡単な実装
    - [x] signalの受け取り方の修正
  - ctrl-D
    - [x] 入力待ち状態で何も入力がないときに押すとexitと表示され終了する(bash$ exit)
    - [x] 実行中に押したときも、実行終了後にexitされる
    - [x] 終了ステータスはそのときの終了ステータス
    - 入力中に押すと入力したものを削除できなくなるバグの修正（必要？）
  - ctrl-\
    - [x] 実行中に押すと^\と表示して強制終了する
    - [x] 入力待ち状態だと何も起こらない
    - ワカモレでの確認
    - ^\Quit: 3と出力するように修正
  - ファイル実行
    - [x] 簡単な実装
    - エラーパターンの精査
  - 実行ファイルのサーチ
    - [x] 簡単な実装
    - envを変更
    - エラーパターンの精査

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
  - https://www.atmarkit.co.jp/ait/articles/1708/04/news015.html

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

- 終了ステータス
  - https://ja.wikipedia.org/wiki/%E7%B5%82%E4%BA%86%E3%82%B9%E3%83%86%E3%83%BC%E3%82%BF%E3%82%B9
