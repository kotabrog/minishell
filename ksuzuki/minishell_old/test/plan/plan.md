# plan

## テストケース

- 定義されている個々の動作
- 定義されている組み合わせ（２つ）
- 定義されている組み合わせ（３つ）
- 定義されている組み合わせ（複数）
- 未定義なもの
- 想定したエラー（これだけはフォルダにして、ファイルを複数にわける）

## todo

- githubを用いたファイル共有
- テストケースの作成
- [x] ./minishellで入力待ち状態に
- 入力文字の認識
  - [x] 空白区切り
  - [x]空白以外の文字区切りが必要か調べる->必要なさそう
  - \（対応するか要検討）
  - 文字数の限界
  - コマンド数の限界
  - 記号は隣接していても区切られる（ただし、2>の2はaaa2>では認識されない）
  - 記号系の解釈=>環境変数展開=>実行を意識して格納
  - 環境変数に使用していい文字
- 全体をつなぐ部分の作成
  - [x] 区切った入力文字の受け渡し
  - ストリームの受け渡し
  - 実行コマンドの順番（builtin -> PATHの左から？(pathでの指定法とその実装が必要あるか)）
  - 環境変数がコマンドに変わる法則
    - bashのコマンド(whichででてこないやつ)も、呼び出されるコマンドも、環境変数に入れて実行できる
    - 記号系の解釈=>環境変数展開=>実行
      - パイプやセミコロンなどで途中で環境変数を作成するものについて調べる必要がある
      - 記号系の解釈後、環境変数の展開で記号が現れても、それは文字として認識される
    - コマンドのオプションは実行時に行われる
  - builtinではない実行が、子プロセスで行われるかどうか
- [x] 環境変数の設定(シェルスクリプトは実装しない（a=bで定義するやつ）)
- 機能実装
  - echo
  - echo -n
  - cd
  - pwd
  - export
    - export pipe=|はマルチラインになる（実装しなくていい）
    - export aaaはaaaで登録（中身なし？）
    - export aaa=はaaa=""で登録（おそらく中身空文字列）
  - unset
  - env
    - export aaaで登録すると表示されない
    - export aaa=で登録するとaaa=と表示される
  - exit
  - ;
  - '(マルチラインは未対応でいい)
    - 文字が続いていると一つの文と認識される。例：aaa'aaa'
  - "(マルチラインは未対応でいい)
    - 文字が続いていると一つの文と認識される。例：aaa"aaa"
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



## 参考サイト

- 全体の構成
  - https://brennan.io/2015/01/16/write-a-shell-in-c/
  - https://diary.shuichi.tech/entry/2017/03/31/225633
  - http://www.tohoho-web.com/ex/shell.html
  - http://www.coins.tsukuba.ac.jp/~yas/coins/literacy-2018/2018-06-08/

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
