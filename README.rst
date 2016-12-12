|Travis|_

.. |Travis| image:: https://travis-ci.org/Koji-O/ImageProcessing.svg?branch=master
.. _Travis: https://travis-ci.org/Koji-O/ImageProcessing


C言語で学ぶ実践画像処理
===================================

リポジトリ
-------------

- https://github.com/Koji-O/ImageProcessing


必要環境
---------

1. Opencv version >= 2.0
2. Cmake version >= 2.8
3. Qt5

linux環境、mac環境ではビルドが実行できることを確認しています。

* Qt5に関して。

::
   
   QTDIRを環境変数として設定する必要があります。
   (例)/usr/local/lib/qt5の場合。
   .bashrcに
   export QTDIR=/usr/local/lib/qt5
   を書き込む。

  

ビルド
--------

.. code::

   cd build
   cmake ..
   make


実行方法
---------

.. code::

   ./run.exe datas/lena.png
   
実行するサンプルプログラムを扁壺する場合は,main.cppのコメントアウトを外してください。
   
参考文献
---------
- C言語で学ぶ実践画像処理(2008) 井上 誠喜 (著)他
