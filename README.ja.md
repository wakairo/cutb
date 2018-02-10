CUTB
====

C/C++ Unit Testing Bridge (CUTB)

[![Build Status](https://travis-ci.org/wakairo/cutb.svg?branch=master)](https://travis-ci.org/wakairo/cutb)

CUTBは、C++またはCで書いたユニットテストを、様々な環境（OSやテストフレームワーク）で実行することを目的にしています。
CUTBを使うと、BoostやVisual Studioなどの異なるテストフレームワークを用いて同じテストを実行できます。
こうすることで、複数環境でのソフトウェアテストを容易にすると共に、環境の制限を受けずに最適な開発ツールを利用できるようにします。

利用例としては、以下のようなものを想定しています。

- 組み込みソフトウェアのクロス開発において、開発用マシンとターゲットマシンで同じユニットテストを実行する。
- LinuxとWindowsの両方をサポートする開発で、同じユニットテストをそれぞれの開発環境に適した形で実行する。
- カバレッジ計測ツールとしてGCCのユーティリティであるGcovを使い、デバッガとしてMicrosoft Visual Studioを使う。

CUTBのシンプルな記法は、これらを可能にします。



## 想定している利用シーン

- ユニットテストのポータビリティが必要な場合、もしくは、それを重視する場合。
- 異なるOSをサポートするソフトウェアの開発をしているなどの理由で、ユニットテストを複数の環境で実行したいが、1つのテストフレームワークで全ての環境に対応するのが困難、もしくは、不可能な場合。
- 開発しているソフトウェアの分野や内部構造などの理由から、テストシステム（テスト用のクラスや関数、マクロなど）を自ら構築しているため、テストフレームワークの多機能さは重要でなく、トラブルなく安定してテストを実行できるテストフレームワークを環境に応じて選択できることが重要である場合。
- 計算リソースなどの制約が厳しい環境で動くソフトウェアを開発していて、その実環境でもユニットテストを実行したい場合。
- 組み込みソフトウェア開発において、パソコン上の生産性の高い環境でクラス単位や関数単体の実装とユニットテストを行い、その後、実機上でも同じユニットテストを走らせて実機でも問題ないことを確認する場合。

CUTBは、特定のテストフレームワークに依存していません。そのため、開発環境やテスト実行環境によってフレームワークを使い分けたり、トラブルの少ないフレームワークに移行したりといったことが可能になります。



## テストを実行できる環境

### テストを実行できるテストフレームワーク

- Boost Test Library
- Microsoft Unit Testing Framework

### CUTBが提供する簡易テストフレームワーク

CUTBでは簡易テストフレームワークも利用可能です。
簡易テストフレームワークは、使用している言語機能もコードサイズも非常に少ないため、組み込み開発の実機のような制限の多い環境でユニットテストを走らせる用途に向いています。
ただし、機能も非常に限られます。



## テスト記述の方法

### 簡単なテストファイルの例

```
#include "cutb_config.h"

CUTB_TEST_GROUP(ArithmeticOperationTest)

CUTB_TEST(Addition)
{
    CUTB_ASSERT_EQ_LONG(2, 1+1);
}

CUTB_TEST(Multiplication)
{
    CUTB_ASSERT_EQ_LONG(6, 2*3);
}

CUTB_TEST_GROUP_END;
```

### テスト定義マクロ

- `CUTB_TEST_GROUP(test_group_name)` ： テストグループの始まりを示します。
- `CUTB_TEST_GROUP_END` ： テストグループの終わりを示します。このマクロの後ろには、続けてセミコロン（ ; ）が必要です。
- `CUTB_TEST(test_name)` ： テストを定義します。`CUTB_TEST_GROUP`と`CUTB_TEST_GROUP_END`の間で利用します。

テストグループは、1つのテストファイルの中で、複数定義することが出来ます。

テスト名とテストグループ名では、アンダースコア（ _ ）を使わないことを推奨します。理由は[Google TestのFAQ](http://opencv.jp/googletestdocs/FAQ.html#faq-why-should-not-test-case-names-and-test-names-contain-underscore)をご覧下さい。

### アサート

アサートには以下の4種類があります。

- `CUTB_ASSERT(condition)` ： `condition` が真であるかを確認します。
- `CUTB_ASSERT_EQ_LONG(expected, actual)` ： `expected` と `actual` の両方の値を `long` に変換し、この2つの値が等しいかを確認します。
- `CUTB_ASSERT_EQ_ULONG(expected, actual)` ： `expected` と `actual` の両方の値を `unsigned long` に変換し、この2つの値が等しいかを確認します。
- `CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)` ： `expected` と `actual` の差を計算し、その差が `tolerance` 以内であることを確認します。

### CUTB設定用ヘッダ（cutb_config.h）

cutb_config.hは、テストの実行環境に合わせた設定を記述するためのヘッダファイルです。
cutb_config.hは実行環境ごとに用意します。
コンパイルにおいて、どのcutb_config.hをインクルードするかは、インクルードパスの設定で行います。

cutb_config.hに記述する具体的な内容は、以下の「用途別の利用方法」の項目をご覧下さい。

なお、ファイル名はcutb_config.hである必要はありません。ただ、当然ですが、この役割を果たす全てのファイル名は一貫して同じ名前である必要があります。そして、そのファイル名を`#include`で指定する必要があります。

また、cutb_config.hを間接的にインクルードしても問題ありません。例えば、テスト用のヘルパー関数などのために、全てのテストファイルがtest_helper.hをインクルードしているなら、test_helper.hに`#include "cutb_config.h"`と記述する方法があります。



## Getting Started

### サンプルの実行に必要な環境の準備

Microsoft Unit Testing Framework のサンプルを実行するには、2012以降の Visual Studio が必要です。エディションはCommunityでも大丈夫です。

それ以外のサンプルの実行には、POSIX環境（UNIX互換環境）が必要です。OSがWindowsの場合は、CygwinやWindows Subsystem for Linux、または、VirtualBoxによるLinux仮想マシンなどが利用できます。

POSIX環境には g++ 、 gcov 、 make （GNU Make）、及び、doxygenをインストールして下さい。環境によっては、gcovはg++をインストールすると、同時にインストールされます。

Ubuntuでは以下のコマンドでこれらをインストールできます。
```
sudo apt install g++ make doxygen
```

Boost Test Libraryなどの外部のテストフレームワークを利用したサンプルを実行するには、それぞれのテストフレームワークについてもPOSIX環境へインストールを行って下さい。例えば、UbuntuでのBoost Test Libraryのインストールは、`sudo apt install libboost-test-dev`で行えます。

### Microsoft Unit Testing Framework のサンプルの実行
1. `example/runner/msvc`にある`cutbExample.sln`を Visual Studio で開きます。
2. メニューから「テスト - 実行 - 全てのテスト」を選択するとテストが実行されます。

### POSIX環境向けサンプルの実行
1. `example/runner/`の下にあるディレクトリの1つに移動します。（例えば`cd example/runner/simple/`）
2. `make test`でテストが実行されます。
3. 続けて`gcov *.gcda`を実行すると、拡張子がgcovのファイルにカバレッジの結果が出力されます。

### Doxygenによるテストドキュメントサンプルの作成
1. `example/docs/`へ移動します。
2. `doxygen Doxyfile`を実行すると`html/`にドキュメントが作成されます。
3. `example/docs/html/index.html`をブラウザで開きます。

### CUTBテストスクリプトのサンプルの編集

サンプルのテストは`example/test/`の下にあります。

試しにテストを追加する場合は、既存のテストファイルへ書き加えるか、
`_test.cpp`で終わる名前で新たなテストファイルをこのフォルダに作成して下さい。

テストファイルを追加した場合、Microsoft Unit Testing Frameworkのサンプルについては、新たなテストファイルの追加操作をVisual Studioで行って下さい。

POSIX環境向けサンプルでは、GNU Makeのワイルドカード機能を使っているため、`_test.cpp`で終わるファイルを`example/test/`に置けば、自動的に処理対象になります。



## 用途別の利用方法

### Boost Test Library

Boost Test Libraryを利用するときは、`cutb/bridge/boosttest.h`をインクルードしたCUTB設定用ヘッダ（cutb_config.h）を使用します。

利用例は、`example/runner/boosttest`をご覧下さい。

なお、Ubuntuでは以下のコマンドでBoost Test Libraryをインストールできます。
```
sudo apt install libboost-test-dev
```

### Microsoft Unit Testing Framework

Microsoft Unit Testing Frameworkを利用するときは、`cutb/bridge/msvc.h`をインクルードしたCUTB設定用ヘッダ（cutb_config.h）を使用します。

テストを実行するためのVisual Studio projectの例は、`example/runner/msvc`をご覧下さい。

なお、このフレームワークには、TEST_METHODやTEST_CLASSといった名前のマクロがありますので、マクロ名の衝突にはご注意下さい。

また、 Microsoft Unit Testing Framework for C++ が利用できるのは Visual Studio 2012 以降であることにもご注意下さい。

ちなみに、CUTB_TEST_GROUP_ENDの直後のセミコロンは、Visual Studioに起因しています。
セミコロンをマクロ、つまり、CUTB_TEST_GROUP_ENDに含める実装も検討しましたが、
こうするとVisual Studio 2015では、アサートがある行に付けたブレイクポイントでデバッガの実行が一時停止しない現象がよく発生しました。

#### 制限事項
ドキュメントウィンドウで、ショートカットキーや右クリックメニューを使って、テストを1つだけ実行またはデバッグすることが出来ません。
テスト1つの実行またはデバッグをするには、テストエクスプローラーウインドウで目的のテスト右クリックして下さい。


### CUTBが提供する簡易テストフレームワーク

簡易テストフレームワークを利用する場合は、フレームワークのタイプとアサートのタイプの2つをCUTB設定用ヘッダ（cutb_config.h）で指定します。フレームワークとアサートの組み合わせに制限はありません。

どの組み合わせで利用した場合でも、アサートの失敗が発生した場合は、そこで処理が停止します。自動的に次のテストが実行されることはありません。ゼロ除算のような実行時エラーが発生した場合に自動で復帰して次のテストを実行するような機能もありません。

この簡易テストフレームワークは、組み込み開発のターゲットマシン（実機）のような制限の多い環境でもユニットテストを実行可能にすることを目的としています。そのため、OSの機能は全く使っておらず、CやC++の標準ライブラリでさえほとんど使っていません。また、コードサイズも小さくしています。しかし、その裏返しとして、その範囲でできる機能のみとなっています。
したがって、何らかの理由で他のテストフレームワークでは問題があるときにだけ、簡易テストフレームワークを利用することを推奨します。

なお、環境の制限のせいで古いコンパイラしか使えない場合を考慮しているため、簡易テストフレームワークはC++03でもコンパイルできるように実装しています。


#### フレームワークの種類

##### Simple type

先頭から、もしくは、目的のテストを頭出ししてから、テストを1つずつ順に実行することが出来ます。

利用するには、CUTB設定用ヘッダ（cutb_config.h）で`cutb/framework/simple.h`をインクルードします。
また、`src/cutb_framework_simple_core.cpp`をコンパイルしてリンクする必要があります。

利用できるAPIは、[Doxygenドキュメント](https://wakairo.github.io/cutb-doxydocs/classcutb_1_1_test_manager.html)をご覧下さい。

利用例は、`example/runner/simple`をご覧下さい。

アサートの失敗や実行時エラーが発生すると、テストはそこで停止します。したがって、次のテストから再開するには何らかの操作が必要になります。
利用例では、それぞれのテストを実行する前にテスト番号を表示しており、失敗したテスト番号の次の番号を引数にしてテストを再起動させることで、次のテストから再開できるようにしています。

なお、テスト名などを取得するAPIもありますので、テスト名などを使ってテストを頭出しするプログラムを書くことも出来ます。

##### Minimum type in C++ (mincpp type)

静的オブジェクトのコンストラクタを利用してテストを呼び出します。
そのため、テストの実行順は、静的オブジェクトのコンストラクタが呼ばれる順番になります。
したがって、動的にテストの実行順を変更したりテストを途中から始めたりすることはできませんし、そもそもこのタイプにはAPI関数の類いがありません。

また、標準ライブラリやユーザーのライブラリなどにある静的オブジェクトの初期化タイミングにも注意が必要です。テストが呼ばれる前に初期化が必要な静的オブジェクトがあるかもしれません。例えば、ユニットテストの中で`cout`などの標準入出力ストリームを利用している場合は、`std::ios_base::Init`などを正しく利用して、テストが呼び出される前に標準入出力ストリームが初期化されるようにする必要があります。

以上の制約から、**mincppは利用せず、代わりにsimpleを利用することを推奨**します。
想定しているmincppの利用シーンは、ユニットテストを呼び出すためのコードをどうしても極限まで減らしたいときだけです。

mincppを利用するには、CUTB設定用ヘッダ（cutb_config.h）で`cutb/framework/mincpp.h`をインクルードします。

利用例は、`example/runner/mincpp`をご覧下さい。


#### アサートの種類

##### exit() を用いたアサート

アサートに失敗すると、fprintf()で標準エラー出力にメッセージを出力した後、exit()でプログラムを終了します。

exit() を用いたアサートを利用するには、CUTB設定用ヘッダ（cutb_config.h）で`cutb/assert/exit.h`をインクルードします。
また、`src/cutb_assert_exit.cpp`をコンパイルしてリンクする必要があります。

利用例は、`example/runner/simple`をご覧下さい。

##### C標準ライブラリのアサートマクロを用いたアサート

C標準ライブラリのアサートマクロによるアサートを利用するには、CUTB設定用ヘッダ（cutb_config.h）で`cutb/assert/std.h`をインクルードします。

利用例は、`example/runner/mincpp`をご覧下さい。

このアサートを利用する利点は、テスト実行環境において必要とするものがassert()のみだということです。
欠点は、リリースビルドなどでNDEBUGが定義されているとassert()が無効化されるため、テストが出来なくなってしまうことです。
なお、NDEBUGでassert()が無効になることは、C言語の標準規格で定められています。


### テスト実行以外の用途

#### Doxygenを使ったテストドキュメントの作成

Doxygenの設定ファイル（Doxyfile）を適切に設定することで、Doxygenを使ったテストドキュメントの作成が可能です。
このとき鍵となるDoxygenの設定はPREDEFINEDです。
PREDEFINEDを適切に設定することで、CUTBのテスト定義マクロをドキュメント作成に都合の良い形に展開できます。例えば、テストグループは名前空間、テストは関数として、Doxygenに認識させることが出来ます。

利用例は、`example/docs/`をご覧下さい。
このディレクトリへ移動して以下のコマンドを実行すると、`example/test/`にあるテストのHTMLドキュメントが作成されます。作成されたドキュメントは`example/docs/html/index.html`から開くことができます。
```
doxygen Doxyfile
```

なお、Ubuntuでは以下のコマンドでDoxygenをインストールできます。
```
sudo apt install doxygen
```

#### カバレッジの計測（テストが実行されたことの確認）

GCCでコンパイルしている場合、gcovを使ってカバレッジの確認が可能です。
行ごとに実行されたか否かが確認できますので、それぞれのテストについても実行されたかどうかの確認が可能です。

カバレッジの例を見るには`example/runner/`の下のそれぞれのディレクトリ（例えば`example/runner/simple/`）において、
`make test`でテストの実行をした後に、`gcov *.gcda`を実行して下さい。
すると、拡張子がgcovのファイルにカバレッジの結果が出力されます。

なお、プログラムの分岐の網羅率も確認する場合には、`-b`オプションを加えて`gcov -b *.gcda`を実行します。

gcovの詳細については、gcovのマニュアルをご覧下さい。
