|Travis|_ |docs|

.. |Travis| image:: https://travis-ci.org/Koji-O/ImageProcessing.svg?branch=master
.. _Travis: https://travis-ci.org/Koji-O/ImageProcessing

.. |docs| image:: https://readthedocs.org/projects/imageprocessing/badge/?version=latest
   :target: http://imageprocessing.readthedocs.io/en/latest/?badge=latest
   :alt: Documentation Status


C言語で学ぶ実践画像処理
===================================

リポジトリ
-------------

- https://github.com/Koji-O/ImageProcessing

必要環境
---------

1. Opencv version >= 2.0
2. Cmake version >= 2.8
3. boost >= 1.61   
4. Qt5

linux環境、mac環境ではビルドが実行できることを確認しています。

* Qt5に関して。

::
   
   QTDIRを環境変数として設定する必要があります。
   (例)/usr/local/lib/qt5の場合。
   .bashrcに
   export QTDIR=/usr/local/lib/qt5
   を書き込む。

::

   さらに、macの場合、qt4をbrew経由でインストールしているとコンパイルが通らないため、アンインストールするかcmakeを書き直す必要があります。
   
  

ビルド
--------

.. code::

   cd build
   cmake ..
   make


実行方法
---------

.. code::

   ./ip.exe sample/lena.png
   
   
参考文献
---------
- C言語で学ぶ実践画像処理(2008) 井上 誠喜 (著)他
