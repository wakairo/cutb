# CUTBユーザーマニュアル

## 簡単なテスト記述例

```
#include "cutb_config.h"

CUTB_TEST_GROUP(Math)

CUTB_TEST(Addition)
{
    CUTB_ASSERT_EQ_ULONG(2, 1+1);
}

CUTB_TEST(Multiplication)
{
    CUTB_ASSERT_EQ_ULONG(6, 2*3);
}

CUTB_TEST_GROUP_END;
```


## テスト定義マクロ

- `CUTB_TEST_GROUP(test_group_name)` - テストグループの始まりを示します。
- `CUTB_TEST_GROUP_END` - テストグループの終わりを示します。このマクロの後ろには、続けてセミコロンが必要です。
- `CUTB_TEST(test_name)` - テストを定義します。`CUTB_TEST_GROUP`と`CUTB_TEST_GROUP_END`の間で利用します。

テストグループは、1つのテストファイルの中で、複数定義することが出来ます。


## アサート

アサートには以下の4種類があります。

- `CUTB_ASSERT(condition)` - `condition` が、真であるかを確認します。
- `CUTB_ASSERT_EQ_LONG(expected, actual)` - `expected` と `actual` の両方の値を `long` に変換し、この2つの値が等しいかを確認します。
- `CUTB_ASSERT_EQ_ULONG(expected, actual)` - `expected` と `actual` の両方の値を `unsigned long` に変換し、この2つの値が等しいかを確認します。
- `CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)` - `expected` と `actual` の差を計算し、その差が `tolerance` 以内であることを確認します。
