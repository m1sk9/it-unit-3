# CLAUDE.md

## 開発環境

- **OS**: macOS（Apple Silicon）
- **エディタ**: Zed
- **コンパイラ**: Homebrew の GNU GCC 15（`gcc-15` / `g++-15`）
  - `/usr/bin/gcc` は Apple clang．使わない．
- **LSP**: clangd（Apple Command Line Tools 同梱の clangd 21）
- **デバッガ**: CodeLLDB（LLDB ベース．Apple Silicon では GDB は使えない）
- **シェル**: fish 4.x

## 規格（重要）

実験用 Linux 環境の `gcc 7.3.0`（デフォルト `gnu11`）に合わせるため，**C11 を基準**にする．

- `.clangd` で `-std=c11` を指定済み．エディタの診断は C11 ベース．
- コマンドラインで厳密一致が必要なときだけ `gcc -std=gnu11 -o main main.c` と明示する．
- 普段は `gcc -o main main.c` で OK（gcc-15 のデフォルトは C11 を内包するため，C11 範囲内のコードはそのまま通る）．
- C17 / C23 でしか書けない構文は使わない．使えば clangd が警告する．

## ビルド

ビルドシステム（Make / CMake）は **使わない**．各ソースファイルを手動で `gcc` でコンパイルする方針．

```fish
gcc -o main src/1/mul_a.c
./main
```

`mise.toml` で `CC=gcc-15` を設定済みなので，環境変数 `$CC` を読むツールは自動で gcc-15 を使う．

デバッグビルドは `-g` を明示する：

```fish
gcc -g -o main src/X/foo.c
lldb ./main
```

スライドで提示される gdb コマンド（`run` / `break` / `delete` / `continue` / `step` / `next` / `print` / `quit`）は LLDB の GDB 互換 alias でほぼそのまま使える．

## ディレクトリ構成

```
src/
  1/    # レポート課題 1
  2/    # レポート課題 2 など
```

`src/<章>/<課題名>.c` の単位でファイルを置く．1 ファイル＝独立した main を持つ単体プログラム．

## コード規約

`.clang-format`（LLVM ベース，2 スペースインデント，100 桁）と `.clangd`（`-Wall -Wextra -Wpedantic` + clang-tidy `bugprone-* / performance-* / readability-*`）で自動チェックされる．保存時に整形される（Zed の `format_on_save: on`）．

C コードを書く・直すときは以下を守る：

- `int main()` ではなく **`int main(void)`** と書く（C では `()` は「任意引数」を意味する）．
- **`sprintf` は使わず `snprintf`** を使う．バッファ長を必ず渡す．
- 変数宣言は連結しない（`int a, b;` を避けて `int a; int b;` か for 内で宣言）．
- スタック上のローカル配列は `char buf[N] = {0};` のように初期化する．
- 標準ヘッダは必要なものだけ include する（`UnusedIncludes: Strict`）．
- 既存のソースに日本語のコメントが付いている場合，課題説明としての価値があるので残す．新たな説明コメントは原則書かない．

## 既存ソースの修正方針

レポート提出済みの課題コードでも，警告が出ているものは上記規約に沿って書き直して構わない（既に `src/1/` と `src/2/` で対応済み）．アルゴリズムや出力結果が変わらないことを必ず確認する．

## やってはいけないこと

- Make / CMake / 任意のビルドスクリプトを追加すること（手動 `gcc` の方針を崩さない）．
- C17 / C23 専用構文を使うこと（実験室で通らない）．
- `/usr/bin/gcc`（Apple clang）でビルドすること．必ず `gcc-15` を呼ぶ．
- fish のグローバル関数で `gcc` を上書きする提案を勝手にすること（ユーザーが拒否済み）．
- 依存ライブラリの追加（基本は標準ライブラリのみ）．

## ファイル参照

- `.clangd` — clangd 設定（規格・警告・tidy）
- `.clang-format` — フォーマッタ設定
- `.zed/settings.json` — Zed エディタ設定（clangd への引数）
- `.zed/debug.json` — CodeLLDB デバッグ設定
- `mise.toml` — `CC` / `CXX` 環境変数
