.. ImageProcessing documentation master file, created by
   sphinx-quickstart on Fri Jan  6 15:44:25 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ImageProcessing's documentation!
===========================================

ソースドキュメント
--------------------

画像処理についての補足
---------------------

ここではソースについての言及はしないが、画像処理について学んだこと徒然と書き連ねていく。
参考図書で学んだこと以外にOpenCVの使い方を重点的に調べていく。マニュアルはこちら opencv_

.. _opencv : http://docs.opencv.org/trunk/index.html

Contents:

.. toctree::
   :maxdepth: 2

   ch4
   ch5
   ch6      
   ch7   

opencvのコンパイル
-----------------

.. code-block:: bash
               
   clang++  smooth_weigthed.cpp -I/usr/include/opencv2 -L/usr/lib/x86_64-linux-gnu/ 
   
Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

