# example_code

このディレクトリは、基板固有のピン定義と最小のサンプルコードを置くためのものです。

- `src/main.cpp`
  - いま動かしているサンプル
- `samples/`
  - 機能ごとの短いサンプル

使い方:

1. `samples/` から使いたいサンプルを選ぶ
2. 中身を `src/main.cpp` にコピーする
3. 通常サンプルは `nucleo_g474re` env でビルドする
4. USB CDC サンプルだけ `usbcdc` env でビルドする

ビルド例:

```sh
/home/kotek/.platformio/penv/bin/pio run -e nucleo_g474re
/home/kotek/.platformio/penv/bin/pio run -e usbcdc
```

サンプル一覧:

- `samples/sample_sw.cpp`
- `samples/sample_dipsw.cpp`
- `samples/sample_usart.cpp`
- `samples/sample_i2c.cpp`
- `samples/sample_usbcdc.cpp`
