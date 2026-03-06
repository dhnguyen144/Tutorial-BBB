.. _rst-orphan-and-toctree-guide:

==========================================================
Hướng dẫn sử dụng ``orphan`` và ``toctree`` trong file RST
==========================================================

Tài liệu này cung cấp thông tin chi tiết về cách sử dụng hai tính năng quan
trọng trong reStructuredText (RST) khi làm việc với Sphinx: directive
``:orphan:`` và ``.. toctree::``.

.. contents:: Mục lục
   :local:
   :depth: 2

-----------
1. Orphan
-----------

1.1. Orphan là gì?
===================

``:orphan:`` là một metadata markup đặc biệt của Sphinx. Khi được đặt ở **dòng
đầu tiên** của một file RST, nó báo cho Sphinx biết rằng file này không cần
phải được đưa vào bất kỳ ``toctree`` nào mà vẫn không bị cảnh báo
(warning).

Thông thường, nếu một file RST tồn tại trong project Sphinx nhưng không được
liệt kê trong bất kỳ ``toctree`` nào, Sphinx sẽ đưa ra cảnh báo:

.. code-block:: text

   WARNING: document isn't included in any toctree

Sử dụng ``:orphan:`` sẽ tắt cảnh báo này.

1.2. Cú pháp
=============

Đặt ``:orphan:`` ở **dòng đầu tiên** của file RST, trước cả tiêu đề:

.. code-block:: rst

   :orphan:

   ===========================
   Tiêu đề trang
   ===========================

   Nội dung trang ở đây...

.. important::

   ``:orphan:`` **phải** nằm ở dòng đầu tiên của file, trước mọi nội dung
   khác kể cả tiêu đề. Sau ``:orphan:`` cần có một dòng trống trước khi
   bắt đầu nội dung.

1.3. Khi nào nên dùng orphan?
=============================

Sử dụng ``:orphan:`` trong các trường hợp sau:

- **Trang độc lập**: Trang không thuộc cấu trúc mục lục chính nhưng vẫn cần
  tồn tại (ví dụ: trang cảm ơn, trang pháp lý).

- **Trang được liên kết trực tiếp**: Trang chỉ được truy cập qua hyperlink
  nội bộ chứ không qua mục lục.

- **Trang tạm thời hoặc thử nghiệm**: Trang đang trong quá trình phát triển
  mà chưa sẵn sàng đưa vào cấu trúc tài liệu.

- **Trang landing hoặc redirect**: Trang đặc biệt không phù hợp với cấu trúc
  cây mục lục.

1.4. Ví dụ thực tế
===================

**File ``changelog.rst`` - Trang ghi chú thay đổi độc lập:**

.. code-block:: rst

   :orphan:

   ========================
   Lịch sử thay đổi
   ========================

   Phiên bản 2.0
   ==============

   - Thêm tính năng mới X
   - Sửa lỗi Y

   Phiên bản 1.0
   ==============

   - Phiên bản phát hành đầu tiên

**File ``search-help.rst`` - Trang hướng dẫn tìm kiếm:**

.. code-block:: rst

   :orphan:

   ============================
   Hướng dẫn sử dụng tìm kiếm
   ============================

   Sử dụng thanh tìm kiếm ở góc trên bên phải để tìm nội dung.
   Bạn có thể dùng các toán tử ``AND``, ``OR``, ``NOT`` để lọc kết quả.

1.5. Lưu ý quan trọng
======================

- File có ``:orphan:`` vẫn được Sphinx build và tạo HTML bình thường.
- File vẫn có thể được tham chiếu bằng ``:ref:``, ``:doc:`` hoặc hyperlink.
- ``:orphan:`` chỉ ảnh hưởng đến việc Sphinx có yêu cầu file phải nằm trong
  ``toctree`` hay không.
- Trang orphan **sẽ không** xuất hiện trong navigation sidebar trừ khi được
  liên kết thủ công.

-----------
2. Toctree
-----------

2.1. Toctree là gì?
====================

``.. toctree::`` (Table of Contents Tree) là một directive đặc biệt của
Sphinx dùng để xây dựng **cấu trúc cây mục lục** cho tài liệu. Nó cho phép
bạn liên kết nhiều file RST lại với nhau thành một hệ thống tài liệu có tổ
chức, có phân cấp.

Toctree là thành phần cốt lõi để:

- Tạo navigation sidebar (thanh điều hướng bên).
- Xây dựng cấu trúc phân cấp tài liệu.
- Tự động tạo mục lục.
- Xác định thứ tự đọc tài liệu (previous/next).

2.2. Cú pháp cơ bản
====================

.. code-block:: rst

   .. toctree::

      file1
      file2
      folder/file3

Trong đó ``file1``, ``file2``, ``folder/file3`` là đường dẫn tương đối đến
các file RST (không cần phần mở rộng ``.rst``).

**Ví dụ cụ thể** — File ``index.rst``:

.. code-block:: rst

   =================================
   Tài liệu hướng dẫn BeagleBone
   =================================

   Chào mừng bạn đến với tài liệu hướng dẫn.

   .. toctree::

      getting-started
      hardware/gpio
      hardware/led-control
      api-reference

Cấu trúc thư mục tương ứng:

.. code-block:: text

   docs/
   ├── index.rst
   ├── getting-started.rst
   ├── hardware/
   │   ├── gpio.rst
   │   └── led-control.rst
   └── api-reference.rst

2.3. Các tùy chọn (options) của toctree
========================================

2.3.1. ``:maxdepth:`` — Giới hạn độ sâu hiển thị
--------------------------------------------------

Giới hạn số cấp mục lục hiển thị.

.. code-block:: rst

   .. toctree::
      :maxdepth: 2

      getting-started
      advanced-topics

- ``:maxdepth: 1`` — Chỉ hiện tiêu đề cấp 1 của mỗi trang.
- ``:maxdepth: 2`` — Hiện tiêu đề cấp 1 và cấp 2.
- Không đặt ``maxdepth`` — Hiện tất cả các cấp.

2.3.2. ``:caption:`` — Thêm tiêu đề cho nhóm mục lục
------------------------------------------------------

Thêm một tiêu đề phía trên nhóm liên kết trong mục lục.

.. code-block:: rst

   .. toctree::
      :maxdepth: 2
      :caption: Hướng dẫn cơ bản

      installation
      first-steps
      configuration

2.3.3. ``:numbered:`` — Đánh số tự động
----------------------------------------

Tự động đánh số cho các mục và mục con.

.. code-block:: rst

   .. toctree::
      :numbered:

      chapter1
      chapter2
      chapter3

Kết quả: ``1. Chapter 1``, ``2. Chapter 2``, v.v. Các mục con sẽ được đánh
số ``1.1``, ``1.2``, v.v.

2.3.4. ``:titlesonly:`` — Chỉ hiện tiêu đề trang
-------------------------------------------------

Chỉ hiển thị tiêu đề chính (cấp cao nhất) của mỗi trang, bỏ qua các tiêu đề
phụ bên trong trang.

.. code-block:: rst

   .. toctree::
      :titlesonly:

      overview
      details

2.3.5. ``:glob:`` — Sử dụng pattern matching
---------------------------------------------

Cho phép dùng ký tự đại diện (wildcard) để tự động thêm các file phù hợp.

.. code-block:: rst

   .. toctree::
      :glob:

      tutorials/*
      howto/*

Ví dụ này sẽ tự động thêm tất cả các file RST trong thư mục ``tutorials/``
và ``howto/``.

2.3.6. ``:hidden:`` — Ẩn mục lục
---------------------------------

Thêm các trang vào cấu trúc tài liệu (để navigation hoạt động) nhưng **không
hiển thị** danh sách liên kết trên trang hiện tại.

.. code-block:: rst

   .. toctree::
      :hidden:

      secret-page
      internal-notes

Trang vẫn xuất hiện trong sidebar nhưng không hiển thị inline trên trang chứa
toctree.

2.3.7. ``:reversed:`` — Đảo ngược thứ tự
-----------------------------------------

Đảo ngược thứ tự các mục trong toctree. Thường dùng kết hợp với ``:glob:``
để sắp xếp theo thứ tự ngược.

.. code-block:: rst

   .. toctree::
      :glob:
      :reversed:

      blog/*

2.3.8. ``:name:`` — Đặt tên tham chiếu
----------------------------------------

Gán một nhãn (label) cho toctree để có thể tham chiếu đến nó từ nơi khác.

.. code-block:: rst

   .. toctree::
      :name: main-navigation

      home
      about
      contact

2.4. Tùy chỉnh tiêu đề hiển thị
=================================

Bạn có thể đặt tiêu đề khác cho mục trong toctree bằng cú pháp:

.. code-block:: rst

   .. toctree::

      Tiêu đề tùy chỉnh <ten-file>
      Bắt đầu nhanh <getting-started>
      Cài đặt hệ thống <installation>

Thay vì hiện tiêu đề gốc của file ``getting-started.rst``, mục lục sẽ hiện
"Bắt đầu nhanh".

2.5. Sử dụng nhiều toctree
===========================

Một trang có thể chứa **nhiều** toctree để nhóm nội dung:

.. code-block:: rst

   ========================
   Tài liệu dự án
   ========================

   Hướng dẫn người dùng
   ---------------------

   .. toctree::
      :maxdepth: 2
      :caption: Người dùng

      user/installation
      user/quickstart
      user/configuration

   Tài liệu cho nhà phát triển
   ----------------------------

   .. toctree::
      :maxdepth: 2
      :caption: Nhà phát triển

      dev/contributing
      dev/architecture
      dev/api

2.6. Liên kết ngoài trong toctree
==================================

Toctree cũng hỗ trợ liên kết đến URL bên ngoài:

.. code-block:: rst

   .. toctree::

      introduction
      Mã nguồn trên GitHub <https://github.com/user/project>

2.7. Ví dụ thực tế đầy đủ
==========================

Dưới đây là ví dụ hoàn chỉnh cho một file ``index.rst`` của dự án Sphinx:

.. code-block:: rst

   ================================
   Tài liệu Tutorial BeagleBone
   ================================

   Chào mừng bạn đến với tài liệu hướng dẫn sử dụng BeagleBone Black.

   .. toctree::
      :maxdepth: 2
      :caption: Bắt đầu
      :numbered:

      getting-started/introduction
      getting-started/setup
      getting-started/first-project

   .. toctree::
      :maxdepth: 2
      :caption: Phần cứng

      hardware/gpio
      hardware/led-control
      hardware/sensors

   .. toctree::
      :maxdepth: 1
      :caption: Tham khảo

      reference/api
      reference/faq
      Mã nguồn <https://github.com/dhnguyen144/Tutorial-BBB>

   Chỉ mục
   =======

   * :ref:`genindex`
   * :ref:`search`

---------------------------------------------
3. Kết hợp orphan và toctree
---------------------------------------------

3.1. Mối quan hệ giữa orphan và toctree
=========================================

- Mọi file RST trong project Sphinx nên thuộc về ít nhất một ``toctree``,
  nếu không Sphinx sẽ đưa ra cảnh báo.
- ``:orphan:`` được dùng khi bạn **cố ý** muốn file không thuộc bất kỳ
  ``toctree`` nào.
- Nếu file đã nằm trong ``toctree``, **không cần** dùng ``:orphan:``.

3.2. Khi nào dùng cái nào?
===========================

.. list-table::
   :header-rows: 1
   :widths: 40 30 30

   * - Tình huống
     - Dùng toctree
     - Dùng orphan
   * - Trang thuộc cấu trúc mục lục chính
     - ✅
     - ❌
   * - Trang độc lập, liên kết qua hyperlink
     - ❌
     - ✅
   * - Trang đang phát triển / nháp
     - ❌
     - ✅
   * - Trang landing đặc biệt
     - Tùy trường hợp
     - ✅
   * - Trang phụ lục hoặc tham khảo
     - ✅
     - ❌

3.3. Ví dụ kết hợp
===================

**Cấu trúc thư mục:**

.. code-block:: text

   docs/
   ├── index.rst          ← Chứa toctree chính
   ├── guide.rst          ← Nằm trong toctree
   ├── api.rst            ← Nằm trong toctree
   ├── changelog.rst      ← Orphan (không trong toctree)
   └── search-tips.rst    ← Orphan (không trong toctree)

**File ``index.rst``:**

.. code-block:: rst

   =================
   Trang chủ
   =================

   .. toctree::
      :maxdepth: 2

      guide
      api

**File ``changelog.rst``:**

.. code-block:: rst

   :orphan:

   ====================
   Lịch sử thay đổi
   ====================

   Xem :doc:`guide` để biết thêm chi tiết.

**File ``guide.rst``** (tham chiếu đến trang orphan):

.. code-block:: rst

   ====================
   Hướng dẫn sử dụng
   ====================

   Nội dung hướng dẫn...

   Xem thêm :doc:`changelog` để biết các thay đổi mới nhất.

---------------------------------------------
4. Các lỗi thường gặp và cách khắc phục
---------------------------------------------

4.1. Lỗi: document isn't included in any toctree
=================================================

.. code-block:: text

   WARNING: document isn't included in any toctree

**Nguyên nhân**: File RST tồn tại nhưng không nằm trong bất kỳ ``toctree`` nào.

**Cách khắc phục**:

- Thêm file vào một ``toctree``, hoặc
- Thêm ``:orphan:`` vào đầu file nếu file cố ý không thuộc mục lục nào.

4.2. Lỗi: toctree contains reference to nonexisting document
=============================================================

.. code-block:: text

   WARNING: toctree contains reference to nonexisting document 'ten-file'

**Nguyên nhân**: Tên file trong ``toctree`` không khớp với file thực tế.

**Cách khắc phục**: Kiểm tra lại đường dẫn và tên file (không cần ``.rst``).

4.3. Lỗi: orphan không có tác dụng
====================================

**Nguyên nhân**: ``:orphan:`` không nằm ở dòng đầu tiên của file, hoặc có nội
dung trước nó.

**Cách khắc phục**: Đảm bảo ``:orphan:`` là dòng đầu tiên, theo sau bởi một
dòng trống.

---------------------------------------------
5. Tham khảo thêm
---------------------------------------------

- `Sphinx toctree documentation <https://www.sphinx-doc.org/en/master/usage/restructuredtext/directives.html#directive-toctree>`_
- `Sphinx orphan documentation <https://www.sphinx-doc.org/en/master/usage/restructuredtext/field-lists.html#metadata>`_
- `reStructuredText Primer <https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html>`_
